#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
char a[N][N];
int dr[7] = { -1, 0, 1, 1, 1, 0, -1 };
int dc[7] = { 1, 1, 1, 0, -1, -1, -1 };
vii pos[26];
vector<string> w;

void Process() {
  int ix, jx, ansi = 0, ansj = 0, ansi2 = 0, ansj2 = 0;
  for (const string& s : w) {
    bool m = 0;
    for (const ii& p : pos[s[0] - 'A']) {
      for (int i = 0; i < 7; i++) {
        ix = p.first; jx = p.second;
        m = 1;
        for (int j = 0; j < s.length(); j++) {
          if (ix < 0 || jx < 0 || ix >= n || jx >= n || a[ix][jx] != s[j]) {
            m = 0;
            break;
          }
          ix += dr[i];
          jx += dc[i];
        }
        if (m) {
          ansi = 1 + p.first;
          ansj = 1 + p.second;
          ansi2 = 1 + ix - dr[i];
          ansj2 = 1 + jx - dc[i];
          break;
        }
      }
      if (m)
        break;
    }
    if (!m)
      cout << "Not found\n";
    else
      cout << ansi << "," << ansj << " " << ansi2 << "," << ansj2 << "\n";
  }
}

int main() {
  FASTIO();

  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      pos[a[i][j] - 'A'].push_back({ i, j });
    }
  string s;
  while (cin >> s) {
    if (s.find_first_of('0') != string::npos)
      break;
    w.push_back(s);
  }

  Process();

  return 0;
}