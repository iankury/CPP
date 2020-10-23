#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

struct NodeValues {
  int subtree_size;
  ll sum_of_distances;
};

vector<unordered_map<int, NodeValues>> dp(200001);
vector<vi> adj;

NodeValues Recur(int u, int p) {
  auto it = dp[u].find(p);
  if (it != dp[u].end())
    return it->second;
  NodeValues ans = { 1, 0 };
  for (int v : adj[u]) {
    if (v == p)
      continue;
    const NodeValues rec = Recur(v, u);
    ans.subtree_size += rec.subtree_size;
    ans.sum_of_distances += rec.sum_of_distances + rec.subtree_size;
  }
  return dp[u][p] = ans;
}

int main() {
  io();

  int n, u, v;
  cin >> n;

  adj.resize(n + 1);

  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    const NodeValues cur = Recur(i, -1);
    cout << cur.sum_of_distances << " ";
  }
  cout << "\n";

  return 0;
}