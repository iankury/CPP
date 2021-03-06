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

const int N = 30005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[6]{ 0, 1, 5, 10, 25, 50 };
ll dp[6][N];

ll DP(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  dp[i][j] = DP(i - 1, j);
  if (a[i] <= j)
    dp[i][j] += DP(i, j - a[i]);
  return dp[i][j];
}

int main() {
  FASTIO();

  while (cin >> n) {
    memset(dp, -1, sizeof dp);
    memset(dp[0], 0, sizeof dp[0]);
    for (int i = 0; i < 6; i++)
      dp[i][0] = 1;
    ll m = DP(5, n);
    if (m == 1) cout << "There is only 1 way to produce " << n << " cents change.\n";
    else cout << "There are " << m << " ways to produce " << n << " cents change.\n";
    if (cin.eof()) return 0;
  }

  return 0;
}