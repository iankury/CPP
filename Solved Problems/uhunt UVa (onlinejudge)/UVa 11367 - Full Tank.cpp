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

const int N = 1005, F = 102, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, dist[N][F], price[N], nq;

struct Query {
  int c, s, e;
};
Query queries[F];

struct Dijkstra_Node {
  int u, f, d;
  bool operator < (const Dijkstra_Node& p) const {
    return d > p.d;
  }
};
struct Edge {
  int v, w;
};
vector<Edge> adj[N];

void Dijkstra(int source, int capacity) {
  priority_queue<Dijkstra_Node> Q;
  memset(dist, BIG, sizeof dist);
  dist[source][0] = 0;
  Q.push({ source, 0, 0 });
  while (!Q.empty()) {
    Dijkstra_Node cur = Q.top();
    Q.pop();
    if (cur.d > dist[cur.u][cur.f]) continue;
    for (const Edge& edge : adj[cur.u]) {
      if (cur.f >= edge.w)
        if (dist[cur.u][cur.f] < dist[edge.v][cur.f - edge.w]) {
          dist[edge.v][cur.f - edge.w] = dist[cur.u][cur.f];
          Q.push({ edge.v, cur.f - edge.w, dist[edge.v][cur.f - edge.w] });
        }
    }
    if (cur.f < capacity && dist[cur.u][cur.f] + price[cur.u] < dist[cur.u][cur.f + 1]) {
      dist[cur.u][cur.f + 1] = dist[cur.u][cur.f] + price[cur.u];
      Q.push({ cur.u, cur.f + 1, dist[cur.u][cur.f + 1] });
    }
  }
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  for (int i = 0; i < n; i++)
    cin >> price[i];
  for (int i = 0; i < m; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    adj[u].push_back({ v, d });
    adj[v].push_back({ u, d });
  }
  cin >> nq;
  for (int i = 0; i < nq; i++) {
    cin >> queries[i].c >> queries[i].s >> queries[i].e;
  }

  return 1;
}

void Process() {
  for (int i = 0; i < nq; i++) {
    Dijkstra(queries[i].s, queries[i].c);
    int ans = BIG;
    for (int j = 0; j < queries[i].c; j++)
      ans = min(ans, dist[queries[i].e][j]);
    if (ans == BIG)
      cout << "impossible\n";
    else
      cout << ans << "\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}