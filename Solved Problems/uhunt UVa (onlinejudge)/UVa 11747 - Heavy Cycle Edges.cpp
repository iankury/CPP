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

const int N = 25005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, root[N];

struct Edge {
  int u, v, w;
  bool operator < (const Edge& p) const {
    return w < p.w;
  }
};
Edge edges[N];

int Root(int i) {
  return i == root[i] ? i : root[i] = Root(root[i]);
}

void U(int i, int j) {
  root[Root(i)] = Root(j);
}

bool Disjoint(int i, int j) {
  return Root(i) != Root(j);
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  if (!n && !m) return 0;
  for (int i = 0; i < m; i++) 
    cin >> edges[i].u >> edges[i].v >> edges[i].w;

  return 1;
}

void Process() {
  for (int i = 0; i <= n; i++)
    root[i] = i;
  sort(edges, edges + m);
  vi ans;
  bool none = 1;
  for (int i = 0; i < m; i++) {
    if (Disjoint(edges[i].u, edges[i].v)) 
      U(edges[i].u, edges[i].v);
    else {
      ans.push_back(edges[i].w);
      none = 0;
    }
  }
  if (none) cout << "forest\n";
  else {
    sort(ans.begin(), ans.end());
    if (!ans.empty()) cout << ans[0];
    for (int i = 1; i < ans.size(); i++) 
      cout << " " << ans[i];
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}