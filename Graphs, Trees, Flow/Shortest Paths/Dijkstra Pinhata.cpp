#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

class Dijkstra {
  struct Edge {
    int v;
    ll w;
    bool operator < (const Edge& _p) const { return w > _p.w; }
  };
  const ll BIGLL = 0x3f3f3f3f3f3f3f3f;
  const int vertex_ct, edge_ct, source;
  vector<vector<Edge>> adj;
  vector<bool> vis;
  vi pi;
  void DFS(int u) {
    if (vis[u])
      return;
    vis[u] = 1;
    for (const Edge& ed : adj[u])
      DFS(ed.v);
  }
public:
  Dijkstra(int vertex_count, int edge_count, int source)
    : vertex_ct(vertex_count), edge_ct(edge_count), source(source) {
    adj.assign(vertex_count + 1, vector<Edge>());
    pi.resize(vertex_count + 1);
  }
  void Read_Edges() {
    int u, v, w;
    for (int i = 0; i < edge_ct; i++) {
      cin >> u >> v >> w;
      adj[u].push_back({ v, w });
      adj[v].push_back({ u, w });
    }
  }
  vector<ll> Distances() {
    priority_queue<Edge> Q;
    vector<ll> ans(vertex_ct + 1, BIGLL);
    ans[source] = 0;
    pi[source] = -1;
    Q.push({ source, 0 });
    while (!Q.empty()) {
      const auto [u, d] = Q.top();
      Q.pop();
      if (d > ans[u])
        continue;
      for (const Edge& ed : adj[u]) {
        const auto [v, w] = ed;
        if (ans[u] + w < ans[v]) {
          pi[v] = u;
          ans[v] = ans[u] + w;
          Q.push({ v, ans[v] });
        }
      }
    }
    return ans;
  }
  bool Check_Path_Existence(int destination) {
    vis.assign(vertex_ct + 1, 0);
    DFS(source);
    return vis[destination];
  }
  vi Path(int destination) {
    if (!Check_Path_Existence(destination))
      return vi();
    vi path;
    int u = destination;
    while (u != -1) {
      path.push_back(u);
      u = pi[u];
    }
    reverse(begin(path), end(path));
    return path;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  Dijkstra dijkstra(n, m, 1);
  dijkstra.Read_Edges();
  const vector<ll> distances = dijkstra.Distances();
  const vi ans = dijkstra.Path(n);
  if (ans.empty())
    cout << "-1";
  else
    for (int x : ans)
      cout << x << " ";
  cout << "\n";

  return 0;
}