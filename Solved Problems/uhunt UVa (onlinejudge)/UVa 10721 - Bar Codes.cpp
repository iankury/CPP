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

const int N = 51, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
ll n, k, m, dp[N][N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> k >> m;

  return 1;
}

ll DP(ll i, ll j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i < 1 || j < 1 || i < j) return 0;
  if (i == j) return 1;
  if (j == 1) return m >= i;
  ll& ans = dp[i][j];
  ans = 0;
  ll en = min(i - 1, m);
  for (ll ix = 1; ix <= en; ix++)
    ans += DP(i - ix, j - 1);
  return ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  cout << DP(n, k) << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}