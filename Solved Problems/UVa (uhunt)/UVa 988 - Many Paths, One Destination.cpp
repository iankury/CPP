#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
vector<vi> adj;
vi topo, dp;
vector<bool> vis;

bool Blank(const string& s) {
  if (s.empty())
    return 1;
  for (char c : s) 
    if (!isblank(c) && c != '\n')
      return 0;
  return 1;
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  adj.assign(n + 1, vi());
  string s;
  getline(cin, s);
  int u = 0, v;
  while (getline(cin, s)) {
    if (Blank(s))
      break;
    stringstream ss(s);
    ss >> m;
    for (int i = 0; i < m; i++) {
      ss >> v;
      adj[u].push_back(v);
    }
    u++;
  }

  return 1;
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
  if (ct++)
    cout << "\n";
  topo.clear();
  vis.assign(n + 1, 0);
  dp.assign(n + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < n; i++)
    DFS(i);
  reverse(begin(topo), end(topo));
  int ans = 0;
  for (int u : topo) {
    if (adj[u].empty())
      ans += dp[u];
    else
      for (int v : adj[u])
        dp[v] += dp[u];
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}