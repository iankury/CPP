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

const int M = 42, S = 303, BIG = 0x3f3f3f3f;

int ct = 0;
int m, s, p[M], q[M], dp[M][S][S];

bool Read() {
  cin >> m >> s;
  for (int i = 1; i <= m; i++)
    cin >> p[i] >> q[i];

  return 1;
}

int DP(int coin, int i, int j) {
  if (dp[coin][i][j] != -1)
    return dp[coin][i][j];
  int ans = DP(coin - 1, i, j);
  if (i >= p[coin] && j >= q[coin])
    ans = min(ans, 1 + DP(coin, i - p[coin], j - q[coin]));
  return dp[coin][i][j] = ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  memset(dp[0], BIG, sizeof dp[0]);
  for (int i = 0; i <= m; i++)
    dp[i][0][0] = 0;
  int ans = BIG;
  for (int i = 0; i < 301; i++)
    for (int j = 0; j < 301; j++)
      if (i * i + j * j == s * s)
        ans = min(ans, DP(m, i, j));
  if (ans == BIG)
    cout << "not possible\n";
  else
    cout << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}