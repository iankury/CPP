#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
vi adj[N];

bool Blank(const string& s) {
  for (char c : s)
    if (isdigit(c))
      return 0;
  return 1;
}

void Get_Line(string& s) {
  while (getline(cin, s))
    if (!Blank(s)) return;
  s.clear();
}

bool Reaches(int u, int v) {
  for (int w : adj[u])
    if (w == v)
      return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (!n || cin.eof()) return 0;
  for (int i = 1; i <= n; i++)
    adj[i].clear();
  int u, v;
  string s;
  while (1) {
    Get_Line(s);
    if (s.empty()) return 0;
    if (s[0] == '0') break;
    stringstream ss(s);
    ss >> u;
    while (ss >> v) {
      if (!Reaches(u, v))
        adj[u].push_back(v);
      if (!Reaches(v, u))
        adj[v].push_back(u);
    }
  }
  return 1;
}

int dfs_ct, dfs_num[N], dfs_low[N], pi[N], ans = 0;
bool artic[N];

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
}

void Process() {
  dfs_ct = 0;
  memset(dfs_num, 0, sizeof dfs_num);
  memset(dfs_low, 0, sizeof dfs_low);
  memset(pi, 0, sizeof pi);
  memset(artic, 0, sizeof artic);
  DFS(1);
  ans = 0;
  if (artic[1])
    if (adj[1].size() > 1) {
      int last = dfs_low[adj[1][0]];
      for (int v : adj[1])
        if (dfs_low[v] != dfs_low[last]) {
          ans = 1;
          break;
        }
    }
  for (int i = 2; i <= n; i++)
    if (artic[i])
      ans++;
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}