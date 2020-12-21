#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 85, M = 1000000007;
const ll BIG = 0x3f3f3f3f3f3f3f3f;

int ct = 0;
ll n, K;
ll a[N][N];
ll dp[2][9][N][N];
bool vis[2][9][N][N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> K;
  if (K == 0 && n == 0)
    return 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];

  return 1;
}

ll DP(bool ri, int k, int i, int j) {
  if (i < 1 || i > n || j < 1 || j > n || k < 0) {
    return -BIG;
  }
  if (vis[ri][k][i][j]) {
    return dp[ri][k][i][j];
  }
  vis[ri][k][i][j] = 1;
  ll& ans = dp[ri][k][i][j];
  if (a[i][j] < 0)
    k--;
  ans = -BIG;
  ll temp = DP(ri, k, i - 1, j);
  if (temp != -BIG)
    ans = max(ans, temp + a[i][j]);
  temp = DP(!ri, k, i - 1, j);
  if (temp != -BIG)
    ans = max(ans, temp + a[i][j]);
  if (ri) {
    temp = DP(ri, k, i, j - 1);
    if (temp != -BIG)
      ans = max(ans, temp + a[i][j]);
  }
  else {
    temp = DP(ri, k, i, j + 1);
    if (temp != -BIG)
      ans = max(ans, temp + a[i][j]);
  }
  return ans;
}

void Process() {
  memset(vis, 0, sizeof vis);
  cout << "Case " << ++ct << ": ";
  for (int h = 0; h < 2; h++)
    for (int k = 0; k <= K; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          dp[h][k][i][j] = -BIG;
  int st = 0;
  if (a[1][1] < 0)
    st = 1;
  for (int i = st; i <= K; i++) {
    dp[1][i][1][1] = a[1][1];
    vis[1][i][1][1] = 1;
  }
  ll ans = DP(1, K, n, n);
  if (ans == -BIG)
    cout << "impossible\n";
  else
    cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}