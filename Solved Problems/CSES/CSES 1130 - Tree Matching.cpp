#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

class Hopcroft_Karp {
  static constexpr int NIL = 0, INF = 0x3f3f3f3f;
  const vector<vi>& g;
  int n, n_left;
  vi d;

  bool BFS() {
    queue<int> Q;
    d[0] = INF;
    for (int u = 1; u <= n_left; u++) {
      if (match[u] == NIL) {
        d[u] = 0;
        Q.push(u);
      }
      else
        d[u] = INF;
    }
    while (!Q.empty()) {
      const int u = Q.front();
      Q.pop();
      if (d[u] >= d[NIL])
        continue;
      for (const int v : g[u]) {
        const int m = match[v];
        if (d[m] != INF)
          continue;
        d[m] = d[u] + 1;
        Q.push(m);
      }
    }
    return d[NIL] != INF;
  }

  bool DFS(int u) {
    if (u == NIL)
      return 1;
    for (const int v : g[u]) 
      if (d[match[v]] == d[u] + 1 && DFS(match[v])) {
        match[v] = u;
        match[u] = v;
        return 1;
      }
    d[u] = INF;
    return 0;
  }

  void Compute() {
    while (BFS()) 
      for (int u = 1; u <= n_left; u++) 
        if (!match[u] && DFS(u))
          mcbm++;
  }
public:
  int mcbm;
  vi match;

  Hopcroft_Karp(const vector<vi>& g, int n_left) : 
    g(g), 
    n_left(n_left), 
    n(g.size()), 
    mcbm(0), 
    match(vi(n + 1, NIL)),
    d(vi(n + 1))
  { Compute(); }
}; 

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<vi> adj(n + 1, vi()), g(n + 1, vi());
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi nodes[2];

  function<void(int, int, bool)> DFS = [&](int u, int pi, bool side) {
    nodes[side].push_back(u);
    for (int v : adj[u])
      if (v != pi)
        DFS(v, u, !side);
  };

  DFS(1, -1, 0);

  vi encode(n + 1);
  int ct = 1;
  int n_left = nodes[0].size();
  for (int u : nodes[0])
    encode[u] = ct++;
  ct = 1;
  for (int u : nodes[1])
    encode[u] = n_left + ct++;

  for (int u = 1; u <= n; u++)
    for (int v : adj[u]) {
      const int ux = encode[u], vx = encode[v];
      g[ux].push_back(vx);
      g[vx].push_back(ux);
    }

  Hopcroft_Karp hk(g, n_left);
  cout << hk.mcbm << '\n';

  return 0;
}