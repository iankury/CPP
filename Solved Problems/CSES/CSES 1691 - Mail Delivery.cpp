#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class Hierholzer {
  const vector<vi>& g;
  int m;
  list<int> tour;
  vector<vector<bool>> visited_edge;
  void Euler_Tour(list<int>::iterator it, int u) {
    int v;
    for (int i = 0; i < g[u].size(); i++)
      if (!visited_edge[u][i]) {
        v = g[u][i];
        visited_edge[u][i] = 1;
        for (int j = 0; j < g[v].size(); j++)
          if (g[v][j] == u && !visited_edge[v][j]) {
            visited_edge[v][j] = 1;
            break;
          }
        Euler_Tour(tour.insert(it, u), v);
      }
  }
  bool Degree_Check() {
    vi in_dg(g.size(), 0), out_dg(g.size(), 0);
    for (int u = 1; u < g.size(); u++)
      for (int v : g[u]) {
        in_dg[v]++;
        out_dg[u]++;
      }
    for (int u = 1; u < g.size(); u++)
      if ((in_dg[u] & 1) || (out_dg[u] & 1))
        return 0;
    return 1;
  }
public:
  Hierholzer(const vector<vi>& g, int n_of_edges) : g(g), m(n_of_edges) {}
  vi Euler_Tour(int source) { // when impossible returns empty
    if (!Degree_Check())
      return vi();
    tour.clear();
    visited_edge.assign(g.size(), vector<bool>());
    for (int i = 0; i < g.size(); i++)
      visited_edge[i].assign(g[i].size(), 0);
    Euler_Tour(begin(tour), source);
    if (tour.size() != m)
      return vi();
    tour.push_front(source);
    return vi(begin(tour), end(tour));
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
    adj[v].push_back(u);
  }

  return 1;
}

void Process() {
  Hierholzer hierholzer(adj, m);
  vi ans = hierholzer.Euler_Tour(1);
  if (ans.empty()) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  for (int x : ans)
    cout << x << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}