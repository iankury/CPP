#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f, UNVISITED = -1;

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
vector<ll> k, compk, dp;
vector<unordered_set<int>> compressed;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  k.resize(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> k[i];
  int u, v;
  adj.assign(n + 1, vi());
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  return 1;
}

ll DP(int u) {
  if (dp[u] != UNVISITED)
    return dp[u];
  ll& ans = dp[u];
  ans = compk[u];
  ll mx = 0;
  for (int v : compressed[u])
    mx = max(mx, DP(v));
  ans += mx;
  return ans;
}

void Process() {
  vector<vi> scc = Kosaraju(adj).SCC;
  vi root(n + 1);
  compk.assign(scc.size(), 0);
  compressed.assign(scc.size(), unordered_set<int>());
  for (int i = 0; i < scc.size(); i++)
    for (int x : scc[i]) {
      root[x] = i;
      compk[i] += k[x];
    }
  for (int u = 1; u <= n; u++)
    for (int v : adj[u]) 
      if (root[u] != root[v])
        compressed[root[u]].insert(root[v]);
  dp.assign(scc.size(), UNVISITED);
  ll ans = 0;
  for (int i = 0; i < scc.size(); i++)
    ans = max(ans, DP(i));
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}