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

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, en, t, dist[N];

struct Edge {
  int target, w;
};
vector<vector<Edge>> adj;

struct Node {
  int key, d;
  bool operator < (const Node& p) const {
    return d > p.d;
  }
};

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> en >> t >> m;
  adj.clear();
  adj.resize(n + 1);
  int u, v, w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
  }

  return 1;
}

int Dijkstra(int source) {
  memset(dist, BIG, sizeof dist);
  dist[source] = 0;
  priority_queue<Node> Q;
  Q.push({ source, 0 });
  Node u, v;
  while (!Q.empty()) {
    u = Q.top();
    Q.pop();
    for (const Edge& edge : adj[u.key]) {
      v = { edge.target, u.d + edge.w };
      if (v.d < dist[v.key]) {
        dist[v.key] = v.d;
        Q.push(v);
      }
    }
  }
  return dist[en];
}

void Process() {
  if (ct++) cout << "\n";
  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (Dijkstra(i) <= t)
      ans++;
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}