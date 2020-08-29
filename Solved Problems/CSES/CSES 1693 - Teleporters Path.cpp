#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class EulerianPath {
  const vector<vi>& g;
  int n_of_edges, only_st, only_en;
  vi in_dg, out_dg, path;
  void DFS(int u) {
    while (out_dg[u])
      DFS(g[u][--out_dg[u]]);
    path.push_back(u);
  }
  bool Possible() {
    for (int u = 1; u < g.size(); u++) {
      out_dg[u] += g[u].size();
      for (int v : g[u])
        in_dg[v]++;
    }
    for (int u = 1; u < g.size(); u++) {
      if (abs(in_dg[u] - out_dg[u]) > 1)
        return 0;
      if (in_dg[u] > out_dg[u]) {
        if (only_en)
          return 0;
        only_en = u;
      }
      else if (in_dg[u] < out_dg[u]) {
        if (only_st)
          return 0;
        only_st = u;
      }
    }
    return (bool)only_st == (bool)only_en;
  }
  bool Possible(int source, int target) {
    return Possible() && only_st == source && only_en == target;
  }
public:
  EulerianPath(const vector<vi>& g, int n_of_edges) 
    : g(g), only_st(0), only_en(0), n_of_edges(n_of_edges) {
    in_dg.assign(g.size(), 0);
    out_dg.assign(g.size(), 0);
  }
  vi Path() {
    path.clear();
    if (!only_st && !Possible())
      return vi();
    DFS(only_st ? only_st : 1);
    if (path.size() != n_of_edges + 1)
      return vi();
    reverse(begin(path), end(path));
    return path;
  }
  vi Path(int source, int target) {
    if (!Possible(source, target))
      return vi();
    return Path();
  }
};

int n, m;
vector<vi> adj;

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
  EulerianPath eulerian_path(adj, m);
  vi ans = eulerian_path.Path(1, n);
  if (ans.empty()) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  else {
    for (int x : ans)
      cout << x << " ";
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}