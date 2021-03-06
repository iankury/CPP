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

const int N = 105, M = 1005, Q = 10055;

int ct = 0;
int n, m, q, root[N], target, ans, c1[Q], c2[Q];
bool found;

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
vii adj[N];
vi S;
vector<bool> vis;

void DFS(int u) {
  if (found || vis[u]) return;
  vis[u] = 1;
  if (u == target) {
    found = 1;
    return;
  }
  int v = 0, w = 0;
  for (ii& p : adj[u]) {
    v = p.first;
    w = p.second;
    S.push_back(w);
    DFS(v);
    if (found) return;
    S.pop_back();
  }
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m >> q;
  if (!n && !m && !q) return 0;
  for (int i = 0; i < m; i++)
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
  for (int i = 0; i < q; i++)
    cin >> c1[i] >> c2[i];

  return 1;
}

void Process() {
  for (int i = 0; i <= n; i++)
    root[i] = i;
  if (ct++) cout << "\n";
  cout << "Case #" << ct << "\n";
  for (int i = 0; i <= n; i++)
    adj[i].clear();
  sort(edges, edges + m);
  int u, v, w;
  for (int i = 0; i < m; i++) {
    u = edges[i].u; 
    v = edges[i].v; 
    w = edges[i].w;
    if (Disjoint(u, v)) {
      U(u, v);
      adj[u].push_back({ v, w });
      adj[v].push_back({ u, w });
    }
  }
  for (int i = 0; i < q; i++) {
    found = 0;
    vis.assign(n + 1, 0);
    S.clear();
    target = c2[i];
    DFS(c1[i]);
    if (found) {
      sort(S.begin(), S.end());
      if (!S.empty()) 
        cout << S[S.size() - 1] << "\n";
    }
    else cout << "no path\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}