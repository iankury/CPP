#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int n, m;
vector<ll> d;

struct Edge {
  int key;
  ll w;
};
vector<vector<Edge>> adj;

void Bellman_Ford(int source) {
  d.assign(n + 1, 9e18);
  d[source] = 0;
  for (int i = 0; i < n - 1; i++)
    for (int u = 1; u <= n; u++)
      for (const Edge& v : adj[u])
        d[v.key] = min(d[v.key], d[u] + v.w);
}

bool Negative_Cycle() {
  for (int u = 0; u < n; u++)
    for (const Edge& v : adj[u])
      if (d[v.key] > d[u] + v.w)
        return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  adj.resize(n + 1);
  int u, v, w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
  }

  return 1;
}

void Process() {

}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}