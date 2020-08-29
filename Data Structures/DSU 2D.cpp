#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

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

int main() {
  FASTIO();

  

  return 0;
}