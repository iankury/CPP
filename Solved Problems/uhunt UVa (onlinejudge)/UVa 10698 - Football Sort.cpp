#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <iomanip>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 30, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
map<string, int> encode;
string decode[N];

struct Match {
  int k1, k2, s1, s2;
};
vector<Match> matches;

bool LexiLess(const string& s, const string& t) {
  char c, d;
  int en = min(s.length(), t.length());
  for (int i = 0; i < en; i++) {
    c = isalpha(s[i]) ? tolower(s[i]) : s[i];
    d = isalpha(t[i]) ? tolower(t[i]) : t[i];
    if (c != d) return c < d;
  }
  return s.length() < t.length();
}

struct Team {
  int key, score, n_matches, g_for, g_agst, g_diff;
  double perc;
  Team() : score(0), n_matches(0), g_for(0), g_agst(0) {}
  void Compute() {
    g_diff = g_for - g_agst;
    if (n_matches) {
      double d = n_matches * 3;
      perc = (double)score * 100. / d;
    }
    else perc = -3456.;
  }
  bool operator < (const Team& p) const {
    if (score == p.score) {
      if (g_diff == p.g_diff) {
        return g_for == p.g_for ? LexiLess(decode[key], decode[p.key]) : g_for > p.g_for;
      }
      return g_diff > p.g_diff;
    }
    return score > p.score;
  }
};
vector<Team> teams;

bool Tied(const Team& p, const Team& q) {
  return p.score == q.score && p.g_diff == q.g_diff && p.g_for == q.g_for;
}

bool Read() {
  encode.clear();
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  if (!n && !m) return 0;
  for (int i = 0; i < n; i++) {
    cin >> decode[i];
    encode[decode[i]] = i;
  }
  char trash;
  string s, t;
  matches.resize(m);
  for (int i = 0; i < m; i++) {
    cin >> s >> matches[i].s1 >> trash >> matches[i].s2 >> t;
    matches[i].k1 = encode[s];
    matches[i].k2 = encode[t];
  }

  return 1;
}

void Process() {
  if (ct++) cout << "\n";
  teams.clear();
  teams.resize(n);
  for (int i = 0; i < n; i++)
    teams[i].key = i;
  int u, v, p, q;
  for (int i = 0; i < m; i++) {
    u = matches[i].k1;
    v = matches[i].k2;
    p = matches[i].s1;
    q = matches[i].s2;
    if (p > q) teams[u].score += 3;
    else if (p < q) teams[v].score += 3;
    else {
      teams[u].score += 1;
      teams[v].score += 1;
    }
    teams[u].g_for += p;
    teams[v].g_for += q;
    teams[u].g_agst += q;
    teams[v].g_agst += p;
    teams[u].n_matches++;
    teams[v].n_matches++;
  }
  for (int i = 0; i < n; i++)
    teams[i].Compute();
  sort(teams.begin(), teams.end());
  string rank;
  for (int i = 0; i < n; i++) {
    rank = to_string(i + 1);
    rank.push_back('.');
    if (i && Tied(teams[i], teams[i - 1])) cout << "   ";
    else cout << right << setw(3) << rank;
    cout << right << setw(16) << decode[teams[i].key];
    cout << right << setw(4) << teams[i].score;
    cout << right << setw(4) << teams[i].n_matches;
    cout << right << setw(4) << teams[i].g_for;
    cout << right << setw(4) << teams[i].g_agst;
    cout << right << setw(4) << teams[i].g_diff;
    if (teams[i].perc < -3.) cout << "    N/A";
    else cout << right << setw(7) << fixed << setprecision(2) << teams[i].perc;
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}