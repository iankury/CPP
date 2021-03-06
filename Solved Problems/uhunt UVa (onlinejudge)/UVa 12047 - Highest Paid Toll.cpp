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

const int N = 10005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, s, t, p, ds[N], dt[N];

struct Edge {
  int key, w;
};
vector<vector<Edge>> adj, rev_adj;

struct Node {
  int key, d;
  bool operator < (const Node& node) const {
    return d > node.d;
  }
};

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m >> s >> t >> p;
  adj.clear();
  adj.resize(n + 1);
  rev_adj.clear();
  rev_adj.resize(n + 1);
  int u, v, w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
    rev_adj[v].push_back({ u, w });
  }

  return 1;
}

void Dijkstra(int source, int* arr, const vector<vector<Edge>>& _adj) {
  priority_queue<Node> Q;
  Q.push({ source, 0 });
  arr[source] = 0;
  Node u, v;
  while (!Q.empty()) {
    u = Q.top();
    Q.pop();
    for (const Edge& edge : _adj[u.key]) {
      v = { edge.key, u.d + edge.w };
      if (v.d < arr[v.key]) {
        arr[v.key] = v.d;
        Q.push(v);
      }
    }
  }
}

void Process() {
  memset(ds, BIG, sizeof ds);
  memset(dt, BIG, sizeof dt);
  Dijkstra(s, ds, adj);
  Dijkstra(t, dt, rev_adj);
  int ans = -1, v;
  for (int u = 1; u <= n; u++) 
    for (const Edge& edge : adj[u]) {
      v = edge.key;
      if (ds[u] + edge.w + dt[v] <= p)
        ans = max(ans, edge.w);
    }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (Read() && T--)
    Process();

  return 0;
}