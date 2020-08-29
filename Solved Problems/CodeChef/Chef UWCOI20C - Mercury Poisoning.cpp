#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, NQ = 200005, BIG = 0x3f3f3f3f;

class DSU {
  vector<vii> root;
  vector<vi> rank, cardi;
  ii Root(ii i) {
    if (root[i.first][i.second] == i)
      return i;
    return root[i.first][i.second] = Root(root[i.first][i.second]);
  }
public:
  DSU(int _szr, int _szc) {
    rank.assign(_szr + 1, vi(_szc + 1, 0));
    cardi.assign(_szr + 1, vi(_szc + 1, 1));
    root.assign(_szr + 1, vii(_szc + 1));
    for (int i = 0; i <= _szr; i++)
      for (int j = 0; j <= _szc; j++)
        root[i][j] = { i, j };
  }
  int Cardinality(int ix, int iy) {
    ii _r = Root({ ix, iy });
    return cardi[_r.first][_r.second];
  }
  bool Same(int ix, int iy, int jx, int jy) {
    return Root({ ix, iy }) == Root({ jx, jy });
  }
  void Unite(int ix, int iy, int jx, int jy) {
    if (Same(ix, iy, jx, jy))
      return;
    ii x = Root({ ix, iy }), y = Root({ jx, jy });
    if (rank[x.first][x.second] > rank[y.first][y.second]) {
      root[y.first][y.second] = x;
      cardi[x.first][x.second] += cardi[y.first][y.second];
    }
    else {
      root[x.first][x.second] = y;
      cardi[y.first][y.second] += cardi[x.first][x.second];
      if (rank[x.first][x.second] == rank[y.first][y.second])
        rank[y.first][y.second]++;
    }
  }
};

struct Query {
  int r, c, p, idx;
  bool operator < (const Query& query) const {
    return p < query.p;
  }
};
vector<Query> Q;

struct Cell {
  int r, c, h;
  bool operator < (const Cell& cell) const {
    return h < cell.h;
  }
};
vector<Cell> C;

int n, m, q;
int a[N][N];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int ans[NQ];

void Clear_Borders() {
  for (int i = 0; i < N; i++)
    a[i][0] = a[0][i] = a[i][m + 1] = a[n + 1][i] = BIG;
}

bool Read() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  Q.clear();
  Q.resize(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i].r >> Q[i].c >> Q[i].p;
    Q[i].idx = i;
  }

  return 1;
}

void Process() {
  Clear_Borders();
  C.clear();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      C.push_back({ i, j, a[i][j] });
  sort(rbegin(C), rend(C));
  sort(begin(Q), end(Q));
  DSU dsu(n, m);
  int ix, iy, h, jx, jy;
  for (const Query& query : Q) {
    while (!C.empty() && C.back().h < query.p) {
      ix = C.back().r;
      iy = C.back().c;
      h = C.back().h;
      C.pop_back();
      for (int k = 0; k < 4; k++) {
        jx = ix + dr[k];
        jy = iy + dc[k];
        if (a[jx][jy] <= h) 
          dsu.Unite(ix, iy, jx, jy);
      }
    }
    if (query.p <= a[query.r][query.c])
      ans[query.idx] = 0;
    else
      ans[query.idx] = dsu.Cardinality(query.r, query.c);
  }
  for (int i = 0; i < q; i++)
    cout << ans[i] << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}