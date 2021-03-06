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

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f, SUB_BIG = 923456789;

int ct = 0;
int n, m, q;
vi busy, trg, dist;
queue<int> Q;

struct Edge {
  int key, w;
};
vector<vector<Edge>> adj;

bool Read() {
  if (!(cin >> n))
    return 0;
  if (cin.eof())
    return 0;
  adj.clear();
  adj.resize(n + 5);
  busy.resize(n + 5);
  for (int i = 1; i <= n; i++)
    cin >> busy[i];
  cin >> m;
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back({ v, ((busy[v] - busy[u]) * (busy[v] - busy[u]) * (busy[v] - busy[u])) });
  }
  cin >> q;
  trg.resize(q);
  for (int i = 0; i < q; i++)
    cin >> trg[i];

  return 1;
}

void Bellman_Ford() {
  for (int i = 0; i < n - 1; i++)
    for (int u = 1; u <= n; u++)
      for (const Edge& edge : adj[u])
        if (dist[u] < SUB_BIG)
          dist[edge.key] = min(dist[edge.key], dist[u] + edge.w);
}

void Negative_Cycle() {
  for (int u = 1; u <= n; u++)
    for (const Edge& edge : adj[u]) {
      if (dist[u] < SUB_BIG)
        if (dist[edge.key] > dist[u] + edge.w)
          dist[edge.key] = -BIG;
    }
}

void Process() {
  dist.assign(n + 5, BIG);
  dist[1] = 0;
  Bellman_Ford();
  Negative_Cycle();
  Bellman_Ford();
  cout << "Set #" << ++ct << "\n";
  for (int target : trg) {
    if (target < 2 || target > n)
      cout << "?\n";
    else {
      if (dist[target] < 3 || dist[target] == BIG)
        cout << "?\n";
      else
        cout << dist[target] << "\n";
    }
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}