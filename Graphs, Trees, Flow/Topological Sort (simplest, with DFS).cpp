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

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
bool vis[N];
vi adj[N], ts;

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  int u, v;
  for (int i = 0; i < n; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  return 1;
}

void DFS(int u) {
  vis[u] = 1;
  for (int v : adj[u])
    if (!vis[v])
      DFS(v);
  ts.push_back(u);
}

void Process() {
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < n; i++)
    if (!vis[i])
      DFS(i);
  reverse(ts.begin(), ts.end());
  for (int x : ts)
    cout << x << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}