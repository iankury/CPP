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

const int N = 105, M = 10005, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, p[N], f[N], dp[N][M][2];

bool Read() {
  cin >> m;
  if (cin.eof()) return 0;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> p[i] >> f[i];

  return 1;
}

int DP(int i, int j, bool k) {
  if (dp[i][j][k] != -1) return dp[i][j][k];
  int last = DP(i - 1, j, k);
  int ans = last;
  if (k) {
    if (p[i] <= j) 
      ans = max(ans, DP(i - 1, j - p[i], k) + f[i]);
  }
  else {
    if (p[i] > j) {
      if (m - j + p[i] > 2000) {
        if (j + 200 >= p[i])
          ans = max(ans, DP(i - 1, j + 200 - p[i], 1) + f[i]);
      }
    }
    else {
      if (m - j + p[i] > 2000)
        ans = max(ans, DP(i - 1, j + 200 - p[i], 1) + f[i]);
      else
        ans = max(ans, DP(i - 1, j - p[i], 0) + f[i]);
    }
  }
  return dp[i][j][k] = ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < M; i++) 
    dp[0][i][0] = dp[0][i][1] = 0;
  cout << DP(n, m, 0) << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}