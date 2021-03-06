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

const int N = 20005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, s, t;
vi dist;

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
  adj.clear();
  adj.resize(n);
  cin >> m >> s >> t;
  int u, v, w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
    adj[v].push_back({ u, w });
  }

  return 1;
}

int Dijkstra() {
  dist.assign(n, BIG);
  dist[s] = 0;
  priority_queue<Node> Q;
  Q.push({ s, 0 });
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
  return dist[t];
}

void Process() {
  cout << "Case #" << ++ct << ": ";
  int ans = Dijkstra();
  if (ans == BIG)
    cout << "unreachable";
  else
    cout << ans;
  cout << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}