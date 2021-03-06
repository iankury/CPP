#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, g;
string trash, tournament;
map<string, int> encode;
string decode[N], games[N];

bool LexiLess (const string& p, const string& q) {
  char c, d;
  for (int i = 0; i < min(p.length(), q.length()); i++) {
    c = p[i];
    d = q[i];
    if (isalpha(c))
      c = tolower(c);
    if (isalpha(d))
      d = tolower(d);
    if (c == d) continue;
    return c < d;
  }
  return p.length() < q.length();
}

struct Team {
  int key, score, g_played, wins, ties, losses, goal_difference, goals_scored, goals_against;
  Team() : key(0), score(0), g_played(0), wins(0), ties(0), losses(0),
  goal_difference(0), goals_scored(0), goals_against(0) {}
  bool operator < (const Team& t) const {
    if (score == t.score) {
      if (wins == t.wins) {
        if (goal_difference == t.goal_difference) {
          if (goals_scored == t.goals_scored) {
            if (g_played == t.g_played)
              return LexiLess(decode[key], decode[t.key]);
            return g_played < t.g_played;
          }
          return goals_scored > t.goals_scored;
        }
        return goal_difference > t.goal_difference;
      }
      return wins > t.wins;
    }
    return score > t.score;
  }
};
vector<Team> teams;

bool Read() {
  encode.clear();
  getline(cin, tournament);
  cin >> n;
  getline(cin, trash);
  string name;
  for (int i = 0; i < n; i++) {
    getline(cin, name);
    decode[i] = name;
    if (!encode.count(name))
      encode[name] = i;
  }
  cin >> g;
  getline(cin, trash);
  for (int i = 0; i < g; i++)
    getline(cin, games[i]);

  return 1;
}

void Process() {
  if (ct++) cout << "\n";
  teams.clear();
  teams.resize(n);
  int idx1, idx2, idx3, key1, key2, goals1, goals2;
#define s games[i]
  for (int i = 0; i < g; i++) {

    idx1 = s.find_first_of('#');
    idx2 = s.find_first_of('@', idx1);
    idx3 = s.find_first_of('#', idx2);

    key1 = encode[s.substr(0, idx1)];
    key2 = encode[s.substr(idx3 + 1)];

    goals1 = stoi(s.substr(idx1 + 1, idx2 - idx1 - 1));
    goals2 = stoi(s.substr(idx2 + 1, idx3 - idx2 - 1));
    
    if (goals1 > goals2) {
      teams[key1].wins++;
      teams[key2].losses++;
      teams[key1].score += 3;
    }
    else if (goals1 < goals2) {
      teams[key1].losses++;
      teams[key2].wins++;
      teams[key2].score += 3;
    }
    else {
      teams[key1].ties++;
      teams[key2].ties++;
      teams[key1].score++;
      teams[key2].score++;
    }

    teams[key1].goals_scored += goals1;
    teams[key2].goals_scored += goals2;
    teams[key1].goals_against += goals2;
    teams[key2].goals_against += goals1;
    teams[key1].g_played++;
    teams[key2].g_played++;
  }

  for (int i = 0; i < n; i++) {
    teams[i].goal_difference = teams[i].goals_scored - teams[i].goals_against;
    teams[i].key = i;
  }

  sort(teams.begin(), teams.end());

  cout << tournament << "\n";
  for (int i = 0; i < n; i++) {
    cout << i + 1 << ") " << decode[teams[i].key] << " " << teams[i].score << "p, "
      << teams[i].g_played << "g (" << teams[i].wins << "-" << teams[i].ties << "-" 
      << teams[i].losses << "), " << teams[i].goal_difference << "gd ("
      << teams[i].goals_scored << "-" << teams[i].goals_against << ")\n";
  }
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  getline(cin, trash);
  while (Read() && T--) Process();

  return 0;
}