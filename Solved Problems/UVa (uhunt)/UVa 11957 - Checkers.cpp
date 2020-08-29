#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, dp[N][N];
string s[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 0; i < n; i++)
    cin >> s[i];

  return 1;
}

bool In_Bounds(int i, int j) {
  return i >= 0 && j >= 0 && i < n && j < n;
}

void Up(int& _p, int _q) {
  _p = (_p + _q) % M;
}

int DP(int i, int j) {
  if (!In_Bounds(i, j) || s[i][j] == 'B')
    return 0;
  if (i == 0) {
    if (s[i][j] == '.')
      return 1;
    return 0;
  }
  if (dp[i][j] != -1)
    return dp[i][j];
  int& ans = dp[i][j];
  ans = 0;
  if (In_Bounds(i - 1, j - 1)) {
    if (s[i - 1][j - 1] == '.')
      Up(ans, DP(i - 1, j - 1));
    else
      Up(ans, DP(i - 2, j - 2));
  }
  if (In_Bounds(i - 1, j + 1)) {
    if (s[i - 1][j + 1] == '.')
      Up(ans, DP(i - 1, j + 1));
    else
      Up(ans, DP(i - 2, j + 2));
  }
  return ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (s[i][j] == 'W') {
        cout << "Case " << ++ct << ": " << DP(i, j) << "\n";
        break;
      }
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}