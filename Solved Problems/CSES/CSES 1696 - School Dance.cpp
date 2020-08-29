#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi match;
vector<bool> vis;
vector<vi> adj;

bool Aug(int _l) {
  if (vis[_l])
    return 0;
  vis[_l] = 1;
  for (int _r : adj[_l])
    if (match[_r] == -1 || Aug(match[_r])) {
      match[_r] = _l;
      return 1;
    }
  return 0;
}

int main() {
  int boys, girls, n_edges, u, v, mcbm = 0;
  cin >> boys >> girls >> n_edges;
  adj.resize(boys + girls + 1, vi());
  for (int i = 0; i < n_edges; i++) {
    cin >> u >> v;
    v += boys;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  match.assign(boys + girls + 1, -1);
  for (int l = 1; l <= boys; l++) {
    vis.assign(boys + 1, 0);
    mcbm += Aug(l);
  }
  cout << mcbm << "\n";
  for (int i = 1 + boys; i <= boys + girls; i++)
    if (match[i] != -1)
      cout << match[i] << " " << i - boys << "\n";

  return 0;
}