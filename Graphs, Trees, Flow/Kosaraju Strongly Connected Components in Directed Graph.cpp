#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

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

int n, m;
vector<vi> adj;
vector<bool> vis;

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
  }

  return 1;
}

void Process() {
  Kosaraju kos = Kosaraju(adj);
  cout << "List of Strongly Connected Components:\n";
  for (const vi& scc : kos.SCC) {
    for (int x : scc)
      cout << x << " ";
    cout << "\n\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}