#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class DSU {
  vi root, rank, cardi;
  int Root(int i) {
    return root[i] == i ? i : root[i] = Root(root[i]);
  }
public:
  DSU(int _sz) {
    rank.assign(_sz + 1, 0);
    root.resize(_sz + 1);
    cardi.assign(_sz + 1, 1);
    for (int i = 0; i <= _sz; i++)
      root[i] = i;
  }
  int Cardinality(int i) {
    return cardi[Root(i)];
  }
  bool Same(int i, int j) {
    return Root(i) == Root(j);
  }
  void Unite(int i, int j) {
    if (Same(i, j))
      return;
    int x = Root(i), y = Root(j);
    if (rank[x] > rank[y]) {
      root[y] = x;
      cardi[x] += cardi[y];
    }
    else {
      root[x] = y;
      cardi[y] += cardi[x];
      if (rank[x] == rank[y])
        rank[y]++;
    }
  }
};

struct Edge { int u, v; ll w; };

class Kruskal {
  vector<Edge>& g;
  DSU dsu;
  void Build_MST() {
    vi sorted(g.size());
    for (int i = 0; i < g.size(); i++)
      sorted[i] = i;
    sort(begin(sorted), end(sorted), [this](int px, int qx) {
      return g[px].w < g[qx].w;
      });
    mst_sum = 0;
    for (int idx : sorted)
      if (!dsu.Same(g[idx].u, g[idx].v)) {
        dsu.Unite(g[idx].u, g[idx].v);
        mst_sum += g[idx].w;
        mst.push_back(g[idx]);
      }
  }
public:
  Kruskal(vector<Edge>& g) : g(g), dsu(g.size()) { Build_MST(); }
  ll mst_sum;
  vector<Edge> mst;
};

int n, m;
vector<Edge> edges;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  edges.resize(m);
  for (int i = 0; i < m; i++)
    cin >> edges[i].u >> edges[i].v >> edges[i].w;

  return 1;
}

void Process() {
  Kruskal kru(edges);
  if (kru.mst.size() != n - 1)
    cout << "IMPOSSIBLE\n";
  else
    cout << kru.mst_sum << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}