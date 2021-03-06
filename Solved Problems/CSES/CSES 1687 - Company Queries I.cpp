#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

struct BinaryLifting {
  vector<vi> pi;
  vi node_depth;
  const vector<vi>& adj;
  const int N;
  int Ancestor_At_Distance(int _p, int _d) {
    for (int i = 21; i >= 0; i--)
      if (_d & (1 << i))
        _p = pi[i][_p];
    return _p ? _p : -1;
  }
  void DFS(int u, int p, int depth) {
    node_depth[u] = depth;
    pi[0][u] = p;
    for (int i = 1; i < 22; i++)
      pi[i][u] = pi[i - 1][pi[i - 1][u]];
    for (int v : adj[u])
      if (v != p)
        DFS(v, u, depth + 1);
  }
  BinaryLifting(int start_node, const vector<vi>& adj) 
    : adj(adj), N(adj.size()) {
    pi.assign(23, vi(N, 0));
    node_depth.resize(N);
    DFS(start_node, 0, 0);
  }
};

int main() {
  io();

  int n, q;
  cin >> n >> q;

  vector<vi> adj(n + 1);

  for (int u = 2; u <= n; u++) {
    int p;
    cin >> p;
    adj[p].push_back(u);
  }

  BinaryLifting blift(1, adj);

  for (int i = 0; i < q; i++) {
    int x, k;
    cin >> x >> k;
    cout << blift.Ancestor_At_Distance(x, k) << "\n";
  }

  return 0;
}