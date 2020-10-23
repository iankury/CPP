#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

struct LCA {
  const vector<vi>& adj;
  const int N;
  vector<vi> pi;
  vi node_depth;
  int Ancestor_At_Distance(int _p, int _d) const {
    for (int i = 21; i >= 0; i--)
      if (_d & (1 << i))
        _p = pi[i][_p];
    return _p;
  }
  void LCA_DFS(int u, int p, int depth) {
    node_depth[u] = depth;
    pi[0][u] = p;
    for (int i = 1; i < 22; i++)
      pi[i][u] = pi[i - 1][pi[i - 1][u]];
    for (int v : adj[u])
      if (v != p)
        LCA_DFS(v, u, depth + 1);
  }
  LCA(int start_node, const vector<vi>& adj) : adj(adj), N(adj.size()) {
    pi.assign(23, vi(N, 0));
    node_depth.resize(N);
    LCA_DFS(start_node, 0, 0);
  }
  int Query_Including_Selves(int _i, int _j) const {
    int mn = node_depth[_i] < node_depth[_j] ? _i : _j;
    if (node_depth[_i] > node_depth[_j])
      _i = Ancestor_At_Distance(_i, node_depth[_i] - node_depth[_j]);
    else if (node_depth[_j] > node_depth[_i])
      _j = Ancestor_At_Distance(_j, node_depth[_j] - node_depth[_i]);
    if (_i == _j)
      return mn;
    int i = 21;
    while (pi[0][_i] != pi[0][_j])
      for (; i >= 0; i--)
        if (pi[i][_i] != pi[i][_j]) {
          _i = pi[i][_i];
          _j = pi[i][_j];
          break;
        }
    return pi[0][_i];
  }
};

int Distance(int u, int v, const LCA& lca) {
  if (u == v)
    return 0;
  const int anc = lca.Query_Including_Selves(u, v);
  return lca.node_depth[u] + lca.node_depth[v] - 2 * lca.node_depth[anc];
}

int main() {
  io();

  int n, q, u, v;
  cin >> n >> q;
  vector<vi> adj(n + 1);

  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  LCA lca(1, adj);

  for (int i = 0; i < q; i++) {
    cin >> u >> v;
    cout << Distance(u, v, lca) << "\n";
  }

  return 0;
}