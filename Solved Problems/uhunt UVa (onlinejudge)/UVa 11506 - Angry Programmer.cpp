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
int n, s, t, pcs, wires, offset;
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
  adj[v].push_back({ u, 0, (int)adj[u].size() - 1 });
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
  cin >> pcs;
  if (cin.eof())
    return 0;
  cin >> wires;
  if (!pcs && !wires)
    return 0;
  s = 1;
  t = pcs;
  offset = pcs + 2;
  n = offset * 3 + 5;
  int u, v, w;
  adj.assign(n, vector<Edge>());
  for (int i = 0; i < pcs - 2; i++) {
    cin >> u >> w;
    Add(u, u + offset, w);
  }
  for (int i = 0; i < wires; i++) {
    cin >> u >> v >> w;
    if ((u == s && v == t) || (u == t && v == s))
      Add(s, t, w);
    else if (u == s)
      Add(s, v, w);
    else if (v == s)
      Add(s, u, w);
    else if (u == t)
      Add(v + offset, t, w);
    else if (v == t)
      Add(u + offset, t, w);
    else {
      Add(u + offset, v, w);
      Add(v + offset, v + offset * 2, w);
      Add(v + offset * 2, u, w);
    }
  }

  return 1;
}

void Process() {
  ll maxflow = 0, curflow;
  while (BFS()) {
    st_from.assign(n + 1, 0);
    while (1) {
      curflow = DFS(s, BIG);
      if (!curflow)
        break;
      maxflow += curflow;
    }
  }
  cout << maxflow << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}