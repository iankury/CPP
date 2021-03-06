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

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, dist[N];

struct Edge {
  int key, w;
};
vector<vector<Edge>> adj;

void Bellman_Ford() {
  memset(dist, BIG, sizeof dist);
  dist[0] = 0;
  for (int i = 0; i < n - 1; i++)
    for (int u = 0; u < n; u++)
      for (const Edge& v : adj[u])
        dist[v.key] = min(dist[v.key], dist[u] + v.w);
}

bool Negative_Cycle() {
  for (int u = 0; u < n; u++)
    for (const Edge& v : adj[u])
      if (dist[v.key] > dist[u] + v.w) 
        return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  adj.clear();
  adj.resize(n);
  int u, v, w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
  }

  return 1;
}

void Process() {
  Bellman_Ford();
  if (Negative_Cycle())
    cout << "possible\n";
  else
    cout << "not possible\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (Read() && T--)
    Process();

  return 0;
}