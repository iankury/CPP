#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
vector<vi> adj;

class LCA {
  vector<vi> pi;
  vi node_depth;
  int Ancestor_At_Distance(int _p, int _d) {
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
public:
  LCA(int start_node) {
    pi.assign(23, vi(n + 1, 0));
    node_depth.resize(n + 1);
    LCA_DFS(start_node, 0, 0);
  }
  int Query(int _i, int _j) {
    if (node_depth[_i] > node_depth[_j])
      _i = Ancestor_At_Distance(_i, node_depth[_i] - node_depth[_j]);
    else if (node_depth[_j] > node_depth[_i])
      _j = Ancestor_At_Distance(_j, node_depth[_j] - node_depth[_i]);
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
  int Query_Including_Selves(int _i, int _j) {
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

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  int u, v;
  adj.assign(n + 1, vi());
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  return 1;
}

void Process() {

}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}