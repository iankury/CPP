#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
vector<vi> adj;
vector<bool> vis;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  int u, v;
  adj.assign(n + 1, vi());
  vis.assign(n + 1, 0);
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  return 1;
}

int mx_depth, farthest_node;

void DFS(int u, int p, int depth) {
  if (depth > mx_depth) {
    mx_depth = depth;
    farthest_node = u;
  }
  for (int v : adj[u])
    if (v != p)
      DFS(v, u, depth + 1);
}

int Diameter() {
  mx_depth = 0;
  DFS(1, -1, 0);
  mx_depth = 0;
  DFS(farthest_node, -1, 0);
  return mx_depth;
}

void Process() {

}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}