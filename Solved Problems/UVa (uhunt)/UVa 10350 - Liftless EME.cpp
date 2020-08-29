#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 2222, M = 1000000007, BIG = 0x3f3f3f3f;

struct Edge {
  int v, w;
};

int ct = 0;
int n, m, V;
int dp[N], inc[N];
bool vis[N];
string s;
vector<vector<Edge>> adj;
vi topo;

bool Read() {
  cin >> s;
  if (cin.eof())
    return 0;
  cin >> n >> m;
  V = m * n;
  adj.assign(V, vector<Edge>());
  int u, v, w;
  memset(inc, 0, sizeof inc);
  for (int k = 0; k < n - 1; k++)
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++) {
        u = k * m + i;
        v = (k + 1) * m + j;
        cin >> w;
        adj[u].push_back({ v, w + 2 });
        inc[v]++;
      }

  return 1;
}

void DFS(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (const Edge& ed : adj[u])
    DFS(ed.v);
  topo.push_back(u);
}

void Process() {
  int ans = BIG;
  memset(vis, 0, sizeof vis);
  memset(dp, 0x3f, sizeof dp);
  topo.clear();
  for (int i = 0; i < V; i++) {
    DFS(i);
    if (inc[i] == 0)
      dp[i] = 0;
  }
  reverse(begin(topo), end(topo));
  for (int u : topo)
    for (const Edge& ed : adj[u]) 
      dp[ed.v] = min(dp[ed.v], dp[u] + ed.w);
  for (int i = V - 1; i >= V - m; i--)
    ans = min(ans, dp[i]);
  cout << s << "\n";
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}