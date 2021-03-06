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

const int N = 2005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, ans, dfs_ct;
vi adj[N], dfs_num, dfs_low, vis, S;

bool Read() {
  cin >> n >> m;
  if (!n && !m) return 0;
  for (int i = 1; i <= n; i++)
    adj[i].clear();
  int u, v, p;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> p;
    adj[u].push_back(v);
    if (p == 2) adj[v].push_back(u);
  }

  return 1;
}

void DFS(int u) {
  dfs_num[u] = dfs_low[u] = ++dfs_ct;
  vis[u] = 1;
  S.push_back(u);
  for (int v : adj[u]) {
    if (!dfs_num[v])
      DFS(v);
    if (vis[v])
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
  if (dfs_num[u] == dfs_low[u]) {
    ans++;
    while (1) {
      int v = S.back();
      S.pop_back();
      vis[v] = 0;
      if (u == v) break;
    }
  }
}

void Process() {
  dfs_ct = ans = 0;
  dfs_num.assign(n + 1, 0);
  dfs_low.assign(n + 1, 0);
  vis.assign(n + 1, 0);
  for (int i = 1; i <= n; i++) 
    if (!dfs_num[i])
      DFS(i);
  cout << (ans == 1) << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}