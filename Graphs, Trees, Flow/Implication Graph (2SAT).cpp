#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class Kosaraju {
  vector<bool> vis;
  const vector<vi>& g;
  vector<vi> g_reversed;
  vi vecstack;
  void DFS(int u) {
    if (vis[u])
      return;
    vis[u] = 1;
    for (int v : g[u])
      DFS(v);
    vecstack.push_back(u);
  }
  void DFS2(int u) {
    if (vis[u])
      return;
    vis[u] = 1;
    for (int v : g_reversed[u])
      DFS2(v);
    SCC.back().push_back(u);
  }
public:
  vector<vi> SCC;
  Kosaraju(const vector<vi>& g) : g(g) {
    g_reversed.assign(g.size(), vi());
    vis.assign(g.size(), 0);
    for (int u = 1; u < g.size(); u++) {
      for (int v : g[u])
        g_reversed[v].push_back(u);
      DFS(u);
    }
    vis.assign(g.size(), 0);
    int u;
    while (!vecstack.empty()) {
      u = vecstack.back();
      vecstack.pop_back();
      if (vis[u] == 0) {
        SCC.push_back(vi());
        DFS2(u);
      }
    }
  }
};

class Implication_Graph {
  int idx_last_el, total_nodes;
  constexpr int NEGATE(int _p) { return (_p + idx_last_el) % total_nodes; };
  vector<vi> imp_graph;
  vector<bool> vis;
  vi topo;
  void DFS(int u) {
    if (vis[u])
      return;
    vis[u] = vis[NEGATE(u)] = 1;
    for (int v : imp_graph[u])
      DFS(v);
    topo.push_back(u);
  }
  void TopoSort() {
    vis.assign(total_nodes, 0);
    for (int i = 0; i < total_nodes; i++)
      DFS(i);
    reverse(begin(topo), end(topo));
  }
  void Propagate(int u) {
    if (vis[u])
      return;
    vis[u] = vis[NEGATE(u)] = 1;
    valid_config[u] = true;
    valid_config[NEGATE(u)] = false;
    for (int j : imp_graph[u])
      Propagate(j);
  }
public:
  vector<bool> valid_config;
  Implication_Graph(int idx_last_el) : idx_last_el(idx_last_el) {
    total_nodes = (idx_last_el << 1);
    imp_graph.assign(total_nodes, vi());
  }
  void Add_Implication(int _p, bool state_of_p, int _q, bool state_of_q) {
    if (state_of_p == false)
      _p = NEGATE(_p);
    if (state_of_q == false)
      _q = NEGATE(_q);
    imp_graph[_p].push_back(_q);
  }
  bool Valid() {
    Kosaraju kos(imp_graph);
    vi root(total_nodes);
    for (int i = 0; i < kos.SCC.size(); i++)
      for (int x : kos.SCC[i])
        root[x] = i;
    for (int i = 1; i <= idx_last_el; i++)
      if (root[i] == root[NEGATE(i)])
        return 0;
    valid_config.resize(total_nodes);
    TopoSort();
    vis.assign(total_nodes, 0);
    for (int u : topo)
      Propagate(u);
    return 1;
  }
};

int main() {
  FASTIO();

  return 0;
}