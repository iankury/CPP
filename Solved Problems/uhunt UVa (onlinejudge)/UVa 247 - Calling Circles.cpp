#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 28, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, dfs_ct;
vector<bool> vis;
vi adj[N], dfs_num, dfs_low, S;
map<string, int> nametoi;
string itoname[N];
vector<vi> ans;

void DFS(int u) {
  dfs_num[u] = dfs_low[u] = ++dfs_ct;
  S.push_back(u);
  vis[u] = 1;
  for (int v : adj[u]) {
    if (!dfs_num[v])
      DFS(v);
    if (vis[v])
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
  if (dfs_num[u] == dfs_low[u]) {
    vi ve;
    while (!S.empty()) {
      int v = S[S.size() - 1];
      S.pop_back();
      vis[v] = 0;
      ve.push_back(v);
      if (u == v) break;
    }
    ans.push_back(ve);
  }
}

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
  nametoi.clear();
  ans.clear();
  string s[2];
  int u[2];
  for (int i = 0; i < m; i++) {
    cin >> s[0] >> s[1];
    for (int j = 0; j < 2; j++) {
      if (!nametoi.count(s[j])) {
        nametoi[s[j]] = nametoi.size();
        itoname[nametoi[s[j]]] = s[j];
      }
      u[j] = nametoi[s[j]];
    }
    if (Contains(u[0], u[1])) continue;
    adj[u[0]].push_back(u[1]);
  }

  return 1;
}

void Process() {
  if (ct) cout << "\n";
  dfs_num.assign(n, 0);
  dfs_low.assign(n, 0);
  dfs_ct = 0;
  vis.assign(n, 0);
  cout << "Calling circles for data set " << ++ct << ":\n";
  if (m) {
    for (int i = 0; i < n; i++)
      if (!dfs_num[i]) DFS(i);
    for (int i = ans.size() - 1; i >= 0; i--) {
      cout << itoname[ans[i][ans[i].size() - 1]];
      for (int j = ans[i].size() - 2; j >= 0; j--)
        cout << ", " << itoname[ans[i][j]];
      cout << "\n";
    }
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}