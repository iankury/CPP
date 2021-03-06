#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 150505, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, root[N];

int Root(int i) {
  return i == root[i] ? i : root[i] = Root(root[i]);
}

void U(int i, int j) {
  root[Root(i)] = Root(j);
}

bool Disjoint(int i, int j) {
  return Root(i) != Root(j);
}

struct Edge {
  int u, v, w;
  bool operator < (const Edge& p) const {
    return w < p.w;
  }
};
Edge edges[M];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  for (int i = 0; i < m; i++)
    cin >> edges[i].u >> edges[i].v >> edges[i].w;

  return 1;
}

void Process() {
  sort(edges, edges + m);
  int ans = 0, mn = BIG, sum;
  vi flags;
  for (int i = 0; i <= n; i++)
    root[i] = i;
  for (int i = 0; i < m; i++) 
    if (Disjoint(edges[i].u, edges[i].v)) {
      U(edges[i].u, edges[i].v);
      ans += edges[i].w;
      flags.push_back(i);
    }
  for (int flag : flags) {
    sum = 0;
    ct = 0;
    for (int i = 0; i <= n; i++)
      root[i] = i;
    for (int i = 0; i < m; i++) 
      if (i != flag && Disjoint(edges[i].u, edges[i].v)) {
        U(edges[i].u, edges[i].v);
        sum += edges[i].w;
        ct++;
      }
    if (ct == n - 1)
      mn = min(mn, sum);
  }
  cout << ans << " " << mn << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}