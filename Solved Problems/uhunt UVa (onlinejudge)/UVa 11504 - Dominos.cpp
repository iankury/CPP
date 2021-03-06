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

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, dfs_ct, ans, map[N], contracted_nodes;
vii inc;
bool vis[N];
vi adj[N], dfs_num, dfs_low, S, new_adj[N];

bool Contains(int u, int v) {
  for (int i : new_adj[u])
    if (i == v) return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    new_adj[i].clear();
  }
  cin >> m;
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  return 1;
}

void DFS(int u) {
  dfs_num[u] = dfs_low[u] = ++dfs_ct;   
  S.push_back(u);
  vis[u] = 1;
  for (int v : adj[u]) {
    if (!dfs_num[v]) DFS(v);
    if (vis[v])
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
  if (dfs_num[u] == dfs_low[u]) {
    while (1) {
      int v = S.back();
      S.pop_back();
      vis[v] = 0;
      map[v] = contracted_nodes;
      if (u == v) break;
    }
    contracted_nodes++;
  }
}

void DFS2(int u) {
  vis[u] = 1;
  for (int v : new_adj[u])
    if (!vis[v]) DFS2(v);
}

void Process() {
  dfs_ct = ans = contracted_nodes = 0;
  dfs_num.assign(n + 1, 0);
  dfs_low.assign(n + 1, 0);
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= n; i++) 
    if (!dfs_num[i])
      DFS(i);
  inc.assign(contracted_nodes, { 0, 0 });
  for (int i = 0; i < contracted_nodes; i++)
    inc[i].second = i;
  for (int i = 1; i <= n; i++) 
    for (int v : adj[i]) 
      if (!Contains(map[i], map[v]) && map[i] != map[v]) {
        new_adj[map[i]].push_back(map[v]);
        inc[map[v]].first++;
      }
  memset(vis, 0, sizeof vis);
  sort(inc.begin(), inc.end());
  for (ii i : inc)
    if (!vis[i.second]) {
      ans++;
      DFS2(i.second);
    }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}