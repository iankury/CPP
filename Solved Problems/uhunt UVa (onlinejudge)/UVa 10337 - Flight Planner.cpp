#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, w[10][N], dp[10][N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  n /= 100;
  for (int i = 9; i >= 0; i--)
    for (int j = 0; j < n; j++)
      cin >> w[i][j];

  return 1;
}

bool In_Bounds(int p) {
  return p >= 0 && p < 10;
}

int DP(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (!j) return i ? BIG : 0;
  int& ans = dp[i][j];
  ans = DP(i, j - 1) + 30 - w[i][j - 1];
  if (In_Bounds(i - 1))
    ans = min(ans, DP(i - 1, j - 1) + 60 - w[i - 1][j - 1]);
  if (In_Bounds(i + 1))
    ans = min(ans, DP(i + 1, j - 1) + 20 - w[i + 1][j - 1]);
  return ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  cout << DP(0, n) << "\n\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}