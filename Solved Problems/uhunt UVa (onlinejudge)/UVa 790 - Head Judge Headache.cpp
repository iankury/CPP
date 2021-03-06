#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctype.h>
#include <sstream>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 28, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

bool Blank(const string& s) {
  if (s.empty()) return 1;
  for (char c : s)
    if (isalnum(c))
      return 0;
  return 1;
}

int String_To_Min(const string& s) {
  int hours, minutes, idx = 1;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ':') {
      idx = i;
      break;
    }
  }
  hours = stoi(s.substr(0, idx));
  minutes = stoi(s.substr(idx + 1));
  return hours * 60 + minutes;
}

struct Team {
  int key;
  int AC_at[N];
  vi submissions[N];
  bool solved[N];
  int total_penalty, total_solved;
  Team() {
    memset(AC_at, BIG, sizeof AC_at);
    memset(solved, 0, sizeof solved);
  }
  void Submit(int problem, bool success, int time) {
    if (success) {
      AC_at[problem] = min(AC_at[problem], time);
      solved[problem] = 1;
    }
    else submissions[problem].push_back(time);
  }
  void Compute_Total() {
    total_penalty = total_solved = 0;
    for (int i = 0; i < N; i++) 
      if (solved[i]) {
        total_penalty += AC_at[i];
        for (int sub : submissions[i]) 
          if (sub <= AC_at[i])
            total_penalty += 20;
        total_solved++;
      }
  }
  bool operator < (const Team& team) const {
    if (total_solved == team.total_solved) {
      if (total_penalty == team.total_penalty) 
        return key < team.key;
      return total_penalty < team.total_penalty;
    }
    return total_solved > team.total_solved;
  }
};

int main() {
  FASTIO();

  int t;
  cin >> t;
  string trash, line;
  getline(cin, trash);
  getline(cin, trash);
  while (t--) {
    Team teams[N];
    n = 0;
    char c;
    int team, problem, minutes;
    string time;
    bool result;
    for (int i = 0; i < N; i++)
      teams[i].key = i + 1;
    while (1) {
      if (!getline(cin, line)) break;
      if (Blank(line)) break;
      stringstream ss(line);
      ss >> team;
      n = max(n, team);
      ss >> c;
      problem = (c - 'A');
      ss >> time;
      minutes = String_To_Min(time);
      ss >> c;
      result = (c == 'Y');
      teams[team - 1].Submit(problem, result, minutes);
    }
    for (int i = 0; i < n; i++)
      teams[i].Compute_Total();
    int rank = 1;
    sort(teams, teams + n);
    if (ct++) cout << "\n";
    cout << "RANK TEAM PRO/SOLVED TIME\n";
    for (int i = 0; i < n; i++) {
      if (i && (teams[i].total_penalty != teams[i - 1].total_penalty ||
        teams[i].total_solved != teams[i - 1].total_solved))
        rank = i + 1;
      cout << right << setw(4) << rank <<
        right << setw(5) << teams[i].key;
      if (teams[i].total_solved)
        cout << right << setw(5) << teams[i].total_solved <<
        right << setw(11) << teams[i].total_penalty;
      cout << "\n";
    }
  }

  return 0;
}