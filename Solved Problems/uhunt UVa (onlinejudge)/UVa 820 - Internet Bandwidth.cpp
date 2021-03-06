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

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, s, t;
vi level, st_from;

struct Edge;
vector<vector<Edge>> adj;
struct Edge {
  int v, c, rsd;
  void Augment(int p) {
    c -= p;
    adj[v][rsd].c += p;
  }
};

void Add(int u, int v, int c) {
  adj[u].push_back({ v, c, (int)adj[v].size() });
  adj[v].push_back({ u, c, (int)adj[u].size() - 1 });
}

int DFS(int u, int flow) {
  if (u == t)
    return flow;
  for (; st_from[u] < adj[u].size(); st_from[u]++) {
    Edge& edge = adj[u][st_from[u]];
    if (edge.c && level[edge.v] == 1 + level[u]) {
      int bn = DFS(edge.v, min(flow, edge.c));
      if (bn) {
        edge.Augment(bn);
        return bn;
      }
    }
  }
  return 0;
}

bool BFS() {
  level.assign(n + 1, -1);
  level[s] = 0;
  queue<int> Q;
  Q.push(s);
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    for (const Edge& edge : adj[u])
      if (edge.c && level[edge.v] == -1) {
        level[edge.v] = level[u] + 1;
        Q.push(edge.v);
      }
  }
  return level[t] != -1;
}

bool Read() {
  cin >> n;
  if (cin.eof() || !n)
    return 0;
  adj.clear();
  adj.resize(n + 1);
  cin >> s >> t >> m;
  int u, v, c;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> c;
    Add(u, v, c);
  }

  return 1;
}

void Process() {
  cout << "Network " << ++ct << "\n";
  ll ans = 0, flow;
  while (BFS()) {
    st_from.assign(n + 1, 0);
    while (1) {
      flow = DFS(s, BIG);
      if (!flow)
        break;
      ans += flow;
    }
  }
  cout << "The bandwidth is " << ans << ".\n\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}