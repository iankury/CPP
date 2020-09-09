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
}; // use n_left as offset for right side nodes when building g

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  

  return 0;
}