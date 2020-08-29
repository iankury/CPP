#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

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

class Cycle_Finder {
  enum { WHITE, GRAY, BLACK };
  vi color, cycle;
  int idx;
  const vi& g;
  void DFS(int u) {
    if (color[u] == BLACK)
      return;
    color[u] = GRAY;
    int v = g[u];
    if (color[v] == GRAY) {
      idx = v;
      cycle.push_back(v);
    }
    else
      DFS(v);
    if (idx != -1 && color[idx] == GRAY)
      cycle.push_back(u);
    color[u] = BLACK;
  }
public:
  Cycle_Finder(const vi& g) : g(g) {}
  vector<vi> All_Cycles() {
    idx = -1;
    color.assign(g.size(), WHITE);
    vector<vi> ans;
    for (int i = 1; i < g.size(); i++) {
      cycle.clear();
      DFS(i);
      if (!cycle.empty()) {
        reverse(begin(cycle), end(cycle));
        cycle.pop_back();
        ans.push_back(cycle);
      }
    }
    return ans;
  }
};

class SuccGraph {
  DSU dsu;
  Cycle_Finder cf;
  vector<vi> succ;
  vi idc, lambda;
  const vi& g;
  const int hi = 18, past_limit = 327680;
  void Bottom_Up() {
    succ.assign(g.size(), vi(hi + 1));
    for (int i = 1; i < g.size(); i++)
      succ[i][0] = g[i];
    for (int j = 1; j <= hi; j++)
      for (int i = 1; i < g.size(); i++)
        succ[i][j] = succ[succ[i][j - 1]][j - 1];
  }
  int Lower_Bound(int u, int x) {
    int p = 0, q = past_limit, mid;
    while (p < q) {
      mid = p + (q - p) / 2;
      if (dsu.Same(Succ(u, mid), x))
        q = mid;
      else
        p = mid + 1;
    }
    return p;
  }
public:
  SuccGraph(const vi& g) : g(g), dsu(DSU(g.size())), cf(g) {
    Bottom_Up();
    idc.assign(g.size(), -1);
    lambda.resize(g.size());
    for (const vi& cyc : cf.All_Cycles())
      for (int i = 0; i < cyc.size(); i++) {
        dsu.Unite(cyc[0], cyc[i]);
        idc[cyc[i]] = i;
        lambda[cyc[i]] = cyc.size();
      }
  }
  int Succ(int u, int steps) {
    for (int j = hi; j >= 0; j--)
      if (steps & (1 << j))
        u = succ[u][j];
    return u;
  }
  int SPQ(int u, int v) {
    if (u == v)
      return 0;
    if (dsu.Same(u, v)) {
      if (idc[v] > idc[u])
        return idc[v] - idc[u];
      return idc[v] + lambda[u] - idc[u];
    }
    int ucyc = Succ(u, past_limit);
    int vcyc = Succ(v, past_limit);
    if (!dsu.Same(ucyc, vcyc))
      return -1;
    int ulb = Lower_Bound(u, ucyc);
    int vlb = Lower_Bound(v, vcyc);
    if (ulb == vlb)
      return u == v ? 0 : -1;
    if (idc[u] != -1) 
      return -1;
    if (idc[v] != -1)
      return ulb + SPQ(Succ(u, ulb), v);
    int d = ulb - vlb;
    if (d < 0)
      return -1;
    return Succ(u, d) == v ? d : -1;
  }
};

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, q;
vi a;
vii queries;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> q;
  a.resize(n + 1);
  queries.resize(q);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i < q; i++)
    cin >> queries[i].first >> queries[i].second;

  return 1;
}

void Process() {
  SuccGraph sg(a);
  int u, v;
  for (int i = 0; i < q; i++) {
    tie(u, v) = queries[i];
    cout << sg.SPQ(u, v) << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}