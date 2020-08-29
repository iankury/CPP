#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 21, M = 1000000007, BIG = 0x3f3f3f3f;

int n, m, full_mask, dp[21][1048999];
vector<vi> adj;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  int u, v;
  adj.assign(n, vi());
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u - 1].push_back(v - 1);
  }

  return 1;
}

int DP(int u, int mask) {
  if (u == n) 
    return mask == full_mask;
  if (dp[u][mask] != -1)
    return dp[u][mask];
  int ans = 0;
  for (int v : adj[u])
    if (!(mask & (1 << v)))
      ans = (ans + DP(v, mask | (1 << v))) % M;
  return dp[u][mask] = ans;
}

void Process() {
  --n;
  memset(dp, -1, sizeof dp);
  full_mask = (1 << (n + 1)) - 1;
  cout << DP(0, 1) << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}