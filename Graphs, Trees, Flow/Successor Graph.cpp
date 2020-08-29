#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

class SuccGraph {
  vector<vi> succ;
  const vi& g;
  const int hi = 30;
  void Bottom_Up() {
    succ.assign(g.size(), vi(hi + 1));
    for (int i = 1; i < g.size(); i++)
      succ[i][0] = g[i];
    for (int j = 1; j <= hi; j++)
      for (int i = 1; i < g.size(); i++)
        succ[i][j] = succ[succ[i][j - 1]][j - 1];
  }
public:
  SuccGraph(const vi& g) : g(g) { Bottom_Up(); }
  int Succ(int u, int steps) {
    for (int j = hi; j >= 0; j--) 
      if (steps & (1 << j)) 
        u = succ[u][j];
    return u;
  }
};

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, q;
vi a;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> q;
  a.resize(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  SuccGraph sg(a);
  int u, k;
  for (int i = 0; i < q; i++) {
    cin >> u >> k;
    cout << sg.Succ(u, k) << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}