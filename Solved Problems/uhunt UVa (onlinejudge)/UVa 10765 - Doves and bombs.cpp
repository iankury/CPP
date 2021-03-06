#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
vi adj[N];

bool Contains(int u, int v) {
  for (int i : adj[u])
    if (i == v) return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  if (!n && !m) return 0;
  for (int i = 0; i < n; i++)
    adj[i].clear();
  int u, v;
  while (cin >> u >> v, u > -1) {
    if (!Contains(u, v)) adj[u].push_back(v);
    if (!Contains(v, u)) adj[v].push_back(u);
  }

  return 1;
}

struct Node {
  int key, w;
  bool operator < (const Node& p) const {
    if (w == p.w)
      return key < p.key;
    return w > p.w;
  }
};

int dfs_ct;
vi dfs_num, dfs_low, pi;
vector<bool> artic;
vector<Node> ans;

void DFS(int u) {
  dfs_num[u] = dfs_low[u] = ++dfs_ct;
  for (int v : adj[u]) {
    if (!dfs_num[v]) {
      pi[v] = u;
      DFS(v);
      if (dfs_low[v] >= dfs_num[u])
        artic[u] = 1;
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    else if (v != pi[u])
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);
  }
  if (artic[u]) {
    int pid = 0;
    vector<bool> vis(n, 0);
    stack<int> S;
    for (int i = 0; i < n; i++) {
      if (i == u) continue;
      if (!vis[i]) {
        pid++;
        S.push(i);
        while (!S.empty()) {
          int ux = S.top();
          S.pop();
          if (vis[ux]) continue;
          vis[ux] = 1;
          for (int vx : adj[ux]) 
            if (vx != u)
              S.push(vx);
        }
      }
    }
    if (u || pid > 1)
      ans.push_back({ u, pid });
    else
      artic[0] = 0;
  }
}

void Process() {
  dfs_ct = 0;
  dfs_num.assign(n, 0);
  dfs_low.assign(n, 0);
  pi.assign(n, -1);
  artic.assign(n, 0);
  ans.clear();
  DFS(0);
  sort(ans.begin(), ans.end());

  for (Node& p : ans) {
    if (m-- < 1) break;
    cout << p.key << " " << p.w << "\n";
  }
  for (int i = 0; i < n && m > 0; i++) {
    if (!artic[i]) {
      cout << i << " 1\n";
      m--;
    }
  }
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}