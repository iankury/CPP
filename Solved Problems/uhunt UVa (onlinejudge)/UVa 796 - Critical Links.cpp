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
int n;
vi adj[N];
vii ans;

bool Read() {
  if (!(cin >> n)) return 0;
  if (!n) return 1;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++)
    adj[i].clear();
  int u, v, m;
  char trash;
  for (int i = 0; i < n; i++) {
    cin >> u >> trash;
    cin >> m >> trash;
    for (int j = 0; j < m; j++) {
      cin >> v;
      adj[u].push_back(v);
    }
  }

  return 1;
}

vi dfs_num, dfs_low, pi;
int dfs_ct = 0;

void DFS(int u) {
  dfs_num[u] = dfs_low[u] = ++dfs_ct;
  for (int v : adj[u]) {
    if (!dfs_num[v]) {
      pi[v] = u;
      DFS(v);
      if (dfs_low[v] > dfs_num[u])
        ans.push_back({ min(u, v), max(u, v) });
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    else if (v != pi[u])
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
}

void Process() {
  dfs_num.assign(n, 0);
  dfs_low.assign(n, 0);
  pi.assign(n, -1);
  ans.clear();
  for (int i = 0; i < n; i++)
    if (!dfs_num[i])
      DFS(i);
  cout << ans.size() << " critical links\n";
  sort(ans.begin(), ans.end());
  for (ii p : ans)
    cout << p.first << " - " << p.second << "\n";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}