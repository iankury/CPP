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
int n, a[N];
vector<vi> adj;
vi dist;

bool Read() {
  cin >> n;
  if (n == -1 || cin.eof())
    return 0;
  adj.clear();
  adj.resize(n + 1);
  int neib, v;
  for (int u = 1; u <= n; u++) {
    cin >> a[u] >> neib;
    for (int i = 0; i < neib; i++) {
      cin >> v;
      adj[u].push_back(v);
    }
  }

  return 1;
}

bool BFS() {
  vector<bool> vis(n + 1, 0);
  queue<int> Q;
  Q.push(1);
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    if (vis[u])
      continue;
    vis[u] = 1;
    if (u == n)
      return 1;
    for (int v : adj[u]) 
      Q.push(v);
  }
  return 0;
}

void Bellman_Ford() {
  for (int i = 0; i < n; i++)
    for (int u = 1; u <= n; u++)
      for (int v : adj[u])
        if (dist[u] != -BIG)
          if (dist[u] + a[v] > dist[v] && dist[u] + a[v] > -100)
            dist[v] = min(BIG, dist[u] + a[v]);
}

void Positive_Cycles() {
  for (int u = 1; u <= n; u++)
    for (int v : adj[u])
      if (dist[u] != -BIG)
        if (dist[u] + a[v] > dist[v] && dist[u] + a[v] > -100)
          dist[v] = BIG;
}

void Process() {
  if (!BFS())
    cout << "hopeless\n";
  else {
    dist.assign(n + 1, -BIG);
    dist[1] = 0;
    Bellman_Ford();
    Positive_Cycles();
    Bellman_Ford();
    if (dist[n] > -100)
      cout << "winnable\n";
    else
      cout << "hopeless\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}