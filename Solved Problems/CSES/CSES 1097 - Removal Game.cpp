#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 5005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
ll a[N], dp[N][N], psa[N], vis[N][N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  return 1;
}

ll DP(int l, int r) {
  if (l == r)
    return a[l];
  if (vis[l][r])
    return dp[l][r];
  vis[l][r] = 1;
  ll s1 = psa[r - 1] - psa[l - 1];
  ll s2 = psa[r] - psa[l];
  return dp[l][r] = max(a[l] + s2 - DP(l + 1, r), a[r] + s1 - DP(l, r - 1));
}

void Process() {
  memset(vis, 0, sizeof vis);
  psa[0] = 0;
  psa[1] = a[1];
  for (int i = 2; i <= n; i++)
    psa[i] = a[i] + psa[i - 1];
  cout << DP(1, n) << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}