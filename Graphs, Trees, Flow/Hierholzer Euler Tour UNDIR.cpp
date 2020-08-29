#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class Hierholzer { // UNDIRECTED version
  int n, m;
  vector<vi> g;
  set<ii> used_edges;
public:
  Hierholzer(const vector<vi>& adj, int n_of_edges)
    : g(adj), m(n_of_edges), n(int(adj.size()) - 1) {}
  bool Possible() {
    int src = 1;
    for (int i = 1; i <= n; i++) {
      if (g[i].size() & 1)
        return 0;
      if (!g.empty())
        src = i;
    }
    vector<bool> vis(n + 1, 0);
    function<void(int)> DFS = [&](int u) {
      if (vis[u])
        return;
      vis[u] = 1;
      for (int v : g[u])
        DFS(v);
    };
    DFS(src);
    for (int u = 1; u <= n; u++)
      if (!g[u].empty() && !vis[u])
        return 0;
    return 1;
  }
  vi Euler_Tour(int source_vertex) {
    vi aux, ans;
    aux.reserve(n + 3);
    ans.reserve(n + 3);
    function<void(int)> DFS = [&](int u) {
      aux.push_back(u);
      int v;
      while (!g[u].empty()) {
        v = g[u].back();
        g[u].pop_back();
        if (!used_edges.count({ u, v })) {
          used_edges.insert({ v, u });
          DFS(v);
        }
      }
      ans.push_back(aux.back());
      aux.pop_back();
    };
    DFS(source_vertex);
    reverse(begin(ans), end(ans));
    return ans;
  }
};

int main() {

  return 0;
}