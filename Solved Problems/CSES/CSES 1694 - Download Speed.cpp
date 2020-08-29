#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

class Dinitz {
  int n, m, s, t;
  vi level, st_from;
  struct Edge { int v, c, rsd; };
  vector<vector<Edge>> adj;
  void Augment(Edge& edge, int p) {
    edge.c -= p;
    adj[edge.v][edge.rsd].c += p;
  }
  int DFS(int u, int flow) {
    if (u == t)
      return flow;
    for (; st_from[u] < adj[u].size(); st_from[u]++) {
      Edge& edge = adj[u][st_from[u]];
      if (edge.c && level[edge.v] == 1 + level[u]) {
        int bn = DFS(edge.v, min(flow, edge.c));
        if (bn) {
          Augment(edge, bn);
          return bn;
        }
      }
    }
    return 0;
  }
  bool BFS() {
    level.assign(n + 1, -1);
    level[s] = 0;
    queue<int> Q;
    Q.push(s);
    int u;
    while (!Q.empty()) {
      u = Q.front();
      Q.pop();
      for (const Edge& edge : adj[u])
        if (edge.c && level[edge.v] == -1) {
          level[edge.v] = level[u] + 1;
          Q.push(edge.v);
        }
    }
    return level[t] != -1;
  }
public:
  Dinitz() {}
  Dinitz(int n, int m) : n(n), m(m), s(1), t(n) {
    adj.assign(n + 1, vector<Edge>());
  }
  void Read_Edges() {
    int u, v, c;
    for (int i = 0; i < m; i++) {
      cin >> u >> v >> c;
      adj[u].push_back({ v, c, (int)adj[v].size() });
      adj[v].push_back({ u, 0, (int)adj[u].size() - 1 });
    }
  }
  void Set_Source(int source) { s = source; }
  void Set_Sink(int sink) { t = sink; }
  ll Max_Flow() {
    ll cur_flow, max_flow = 0;
    while (BFS()) {
      st_from.assign(n + 1, 0);
      while (1) {
        cur_flow = DFS(s, 0x3f3f3f3f);
        if (cur_flow == 0)
          break;
        max_flow += cur_flow;
      }
    }
    return max_flow;
  }
};

int main() {
  FASTIO();

  int n, m;
  cin >> n >> m;
  Dinitz dinitz(n, m);
  dinitz.Read_Edges();
  cout << dinitz.Max_Flow() << "\n";

  return 0;
}