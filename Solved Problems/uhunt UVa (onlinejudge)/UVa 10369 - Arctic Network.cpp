#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 505, M = 257055, BIG = 0x3f3f3f3f;

int ct = 0;
int s, n, m, root[N];

struct Point {
  int x, y;
};
Point vertices[N];

struct Edge {
  int u, v;
  double w;
  bool operator < (const Edge& p) const {
    return w < p.w;
  }
};
Edge edges[M];

double D(const Point& p, const Point& q) {
  return sqrt((double)pow(p.x - q.x, 2) + (double)pow(p.y - q.y, 2));
}

int Root(int i) {
  return root[i] == i ? i : root[i] = Root(root[i]);
}

void U(int i, int j) {
  root[Root(i)] = Root(j);
}

bool Disjoint(int i, int j) {
  return Root(i) != Root(j);
}

bool Read() {
  cin >> s;
  if (cin.eof()) return 0;
  cin >> n;
  for (int i = 0; i < n; i++) 
    cin >> vertices[i].x >> vertices[i].y;

  return 1;
}

void Process() {
  double ans = 0;
  m = 0;
  for (int i = 0; i <= n; i++)
    root[i] = i;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      edges[m].u = i;
      edges[m].v = j;
      edges[m].w = D(vertices[i], vertices[j]);
      ++m;
    }
  sort(edges, edges + m);
  ct = 0;
  for (int i = 0; i < m; i++) {
    if (Disjoint(edges[i].u, edges[i].v)) {
      U(edges[i].u, edges[i].v);
      ans = max(ans, edges[i].w);
      if (++ct >= n - s) break;
    }
  }
  cout << fixed << setprecision(2) << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}