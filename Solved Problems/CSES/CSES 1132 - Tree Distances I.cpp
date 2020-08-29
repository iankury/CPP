#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, root, farthest_node, diameter;
vector<vi> adj;
vi max_length;
vector<bool> spine;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  adj.assign(n + 1, vi());
  max_length.assign(n + 1, -1);
  spine.assign(n + 1, 0);
  int u, v;
  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  return 1;
}

void Diam(int u, int p, int depth) {
  if (depth > diameter) {
    diameter = depth;
    farthest_node = u;
  }
  for (int v : adj[u])
    if (v != p)
      Diam(v, u, depth + 1);
}

bool Spine(int u, int p, int depth) {
  if (u == farthest_node)
    spine[u] = 1;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    if (Spine(v, u, depth + 1))
      spine[u] = 1;
  }
  if (spine[u])
    max_length[u] = max(depth, diameter - depth);
  return spine[u];
}

void DFS(int u, int p, int depth) {
  max_length[u] = depth;
  for (int v : adj[u])
    if (v != p)
      DFS(v, u, depth + 1);
}

void Process() {
  if (n == 1) {
    cout << "0\n";
    return;
  }
  diameter = 0;
  Diam(1, -1, 0);
  root = farthest_node;
  diameter = 0;
  Diam(root, -1, 0);
  Spine(root, -1, 0);
  for (int u = 1; u <= n; u++)
    if (spine[u])
      for (int v : adj[u])
        if (spine[v] == 0)
          DFS(v, u, max_length[u] + 1);
  for (int u = 1; u <= n; u++)
    cout << max_length[u] << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}