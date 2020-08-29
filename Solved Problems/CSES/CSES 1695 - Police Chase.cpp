#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class Dinitz {
  int n, m, s, t;
  vi level, st_from;
  ll max_flow;
  struct Edge {
    int v, flow, av_c, tot_c, opp_i;
    Edge() {}
    Edge(int v, int tot_c, int opp_i)
      : v(v), tot_c(tot_c), opp_i(opp_i), av_c(tot_c), flow(0) {}
    void Update(int delta) {
      av_c -= delta;
      flow += delta;
    }
  };
  vector<vector<Edge>> adj;
  void Augment(Edge& edge, int p) {
    edge.Update(p);
    adj[edge.v][edge.opp_i].Update(-p);
  }
  int DFS(int u, int flow) {
    if (u == t)
      return flow;
    for (; st_from[u] < adj[u].size(); st_from[u]++) {
      Edge& edge = adj[u][st_from[u]];
      if (edge.av_c > 0 && level[edge.v] == 1 + level[u]) {
        int rec_flow = DFS(edge.v, min(flow, edge.av_c));
        if (rec_flow) {
          Augment(edge, rec_flow);
          return rec_flow;
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
        if (edge.av_c > 0 && level[edge.v] == -1) {
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
    int u, v, tot_c;
    for (int i = 0; i < m; i++) {
      cin >> u >> v >> tot_c;
      adj[u].push_back({ v, tot_c, (int)adj[v].size() });
      adj[v].push_back({ u, tot_c, (int)adj[u].size() - 1 });
    }
  }
  void Read_Unweighted_Edges() {
    int u, v;
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      adj[u].push_back({ v, 1, (int)adj[v].size() });
      adj[v].push_back({ u, 1, (int)adj[u].size() - 1 });
    }
  }
  void Set_Source(int source) { s = source; }
  void Set_Sink(int sink) { t = sink; }
  ll Max_Flow() {
    ll cur_flow;
    max_flow = 0;
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
  vii Min_Cut() {
    if (Max_Flow() == 0)
      return vii();
    vii ans;
    vector<bool> vis(n + 1, 0);
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    int u;
    while (!Q.empty()) {
      u = Q.front();
      Q.pop();
      for (const Edge& edge : adj[u])
        if (!vis[edge.v] && edge.av_c > 0) {
          vis[edge.v] = 1;
          Q.push(edge.v);
        }
    }
    for (int i = 1; i <= n; i++)
      if (vis[i])
        for (const Edge& edge : adj[i])
          if (!vis[edge.v])
            ans.push_back({ i, edge.v });
    return ans;
  }
};

int main() {
  FASTIO();

  int n, m;
  cin >> n >> m;
  Dinitz dinitz(n, m);
  dinitz.Read_Unweighted_Edges();
  vii mc = dinitz.Min_Cut();
  cout << mc.size() << "\n";
  for (const ii& p : mc)
    cout << p.first << " " << p.second << "\n";

  return 0;
}