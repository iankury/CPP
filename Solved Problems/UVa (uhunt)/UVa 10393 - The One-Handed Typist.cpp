#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int m, n;

int MAP[125];
bool forbidden[11];

bool Read() {
  cin >> m;
  if (cin.eof())
    return 0;
  memset(forbidden, 0, sizeof forbidden);
  cin >> n;
  int x;
  for (int i = 0; i < m; i++) {
    cin >> x;
    forbidden[x] = 1;
  }

  return 1;
}

bool Fail(const string& s) {
  for (char c : s)
    if (forbidden[MAP[c]])
      return 1;
  return 0;
}

void Process() {
  string s;
  set<string> S;
  vector<string> ans;
  int mx = 0;
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (!Fail(s)) {
      S.insert(s);
      mx = max(mx, (int)s.length());
    }
  }
  for (const string& x : S)
    if (x.length() == mx)
      ans.push_back(x);
  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i] << "\n";
}

int main() {
  FASTIO();

  MAP['q'] = MAP['a'] = MAP['z'] = 1;
  MAP['w'] = MAP['s'] = MAP['x'] = 2;
  MAP['e'] = MAP['d'] = MAP['c'] = 3;
  MAP['r'] = MAP['f'] = MAP['v'] = MAP['t'] = MAP['g'] = MAP['b'] = 4;
  MAP['y'] = MAP['h'] = MAP['n'] = MAP['u'] = MAP['j'] = MAP['m'] = 7;
  MAP['i'] = MAP['k'] = 8;
  MAP['o'] = MAP['l'] = 9;
  MAP['p'] = 10;

  while (Read())
    Process();

  return 0;
}