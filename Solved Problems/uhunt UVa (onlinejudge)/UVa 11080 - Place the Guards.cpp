#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 205, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, a[2];
vi adj[N];
bool vis[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  for (int i = 0; i < n; i++)
    adj[i].clear();
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  return 1;
}

bool BFS(int st) {
  queue<int> Q;
  Q.push(st);
  vi color(n, 2);
  color[st] = 0;
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    vis[u] = 1;
    for (int v : adj[u]) {
      if (color[v] == 2) {
        color[v] = 1 - color[u];
        a[color[v]]++;
        Q.push(v);
      }
      else if (color[u] == color[v])
        return 0;
    }
  }
  return 1;
}

void Process() {
  memset(vis, 0, sizeof vis);
  
  bool fail = 0;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      a[0] = 1;
      a[1] = 0;
      if (!BFS(i)) {
        fail = 1;
        break;
      }
      ans += max(1, min(a[0], a[1]));
    }
  }
  if (fail) cout << "-1\n";
  else cout << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}