#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 10055, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, a[N][N];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int dp[M];
bool vis[M];
string s;
vector<vi> adj;
vi topo;

bool Read() {
  cin >> s;
  if (cin.eof())
    return 0;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];

  return 1;
}

bool In_Bounds(int i, int j) {
  return i >= 0 && j >= 0 && i < n && j < m;
}

void DFS(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (int v : adj[u]) 
    DFS(v);
  topo.push_back(u);
}

void Process() {
  int ans = 0;
  adj.assign(M, vi());
  int ix, jx;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) 
      for (int k = 0; k < 4; k++) {
        ix = i + dr[k];
        jx = j + dc[k];
        if (In_Bounds(ix, jx))
          if (a[i][j] > a[ix][jx]) 
            adj[i * m + j].push_back(ix * m + jx);
      }
  topo.clear();
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < M; i++) 
    DFS(i);
  reverse(begin(topo), end(topo));
  memset(dp, -1, sizeof dp);
  for (int u : topo) 
    for (int v : adj[u]) {
      dp[v] = min(dp[v], dp[u] - 1);
      ans = min(ans, dp[v]);
    }
  ans *= -1;
  cout << s << ": " << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}