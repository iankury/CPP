/*
First, provides a check of whether a path exists;
Then, computes the following:
Usual Dijsktra's total weight of Shortest Path;
The path itself.
And through DP:
Total number of Shortest Paths (mod M);
Minimum number of edges in a Shortest Path;
Maximum number of edges in a Shortest Path.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int M = 1000000007;

struct Mint {
  int value;
  Mint(int _value = 0) : value(_value) {}
  operator int() { return value; }
  Mint operator - (const Mint& _a) { int ans = value - _a.value; return ans < 0 ? M + ans : ans; }
  Mint operator + (const Mint& _a) { int ans = value + _a.value; return ans - (ans >= M) * M; }
  Mint operator * (const Mint& _a) { return (ll)value * _a.value % M; }
  bool operator == (const Mint& _a) { return value == _a.value; }
  bool operator != (const Mint& _a) { return value != _a.value; }
};
Mint& operator += (Mint& _a, const Mint& _b) { return _a = _a + _b; }
Mint& operator -= (Mint& _a, const Mint& _b) { return _a = _a - _b; }
Mint& operator *= (Mint& _a, const Mint& _b) { return _a = _a * _b; }
istream& operator >> (istream& is, Mint& _a) { is >> _a.value; return is; }
ostream& operator << (ostream& os, Mint& _a) { os << _a.value; return os; }

const ll BIG = 0x3f3f3f3f3f3f3f3f;
const int N = 500005;

struct Edge {
  int v;
  ll w;
  bool operator < (const Edge& _p) const {
    return w > _p.w;
  }
};

int n, m;
vector<vector<Edge>> adj;
vector<ll> dist;
priority_queue<Edge> Q;
vector<bool> vis;
int pi[N];
vi dijkstra_path;

void Dijkstra(int source) {
  dist.assign(n + 1, BIG);
  dist[source] = 0;
  pi[source] = -1;
  Q.push({ source, 0 });
  int u, v; ll w;
  while (!Q.empty()) {
    u = Q.top().v;
    w = Q.top().w;
    Q.pop();
    if (w > dist[u])
      continue;
    for (const Edge& ed : adj[u])
      if (dist[u] + ed.w < dist[ed.v]) {
        pi[ed.v] = u;
        dist[ed.v] = dist[u] + ed.w;
        Q.push({ ed.v, dist[ed.v] });
      }
  }
}

void Build_Dijkstra_Path(int u) {
  dijkstra_path.clear();
  while (u != -1) {
    dijkstra_path.push_back(u);
    u = pi[u];
  }
  reverse(begin(dijkstra_path), end(dijkstra_path));
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  int u, v, w;
  adj.assign(n + 1, vector<Edge>());
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({ v, w });
    adj[v].push_back({ u, w });
  }

  return 1;
}

void DFS(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (const Edge& ed : adj[u])
    DFS(ed.v);
}

bool Path_Exists(int source, int target) {
  vis.assign(n + 1, 0);
  DFS(source);
  return vis[target];
}

vector<Mint> nsp;
vi mx_ed_in_sp, mn_ed_in_sp;
void Extend_Dijkstra() {
  vi sorted(n);
  for (int i = 0; i < n; i++)
    sorted[i] = i + 1;
  sort(begin(sorted), end(sorted), [](int px, int qx) {
    return dist[px] < dist[qx];
    });
  nsp.assign(n + 1, 0);
  mx_ed_in_sp.assign(n + 1, 0);
  mn_ed_in_sp.assign(n + 1, 0x3f3f3f3f);
  nsp[1] = 1;
  mx_ed_in_sp[1] = mn_ed_in_sp[1] = 0;
  int v;
  for (int u : sorted)
    for (const Edge& ed : adj[u]) {
      v = ed.v;
      if (dist[v] != ed.w + dist[u])
        continue;
      mn_ed_in_sp[v] = min(mn_ed_in_sp[v], 1 + mn_ed_in_sp[u]);
      mx_ed_in_sp[v] = max(mx_ed_in_sp[v], 1 + mx_ed_in_sp[u]);
      nsp[v] += nsp[u];
    }
}

void Process() {
  int source = 1, destination = n;
  if (!Path_Exists(source, destination))
    cout << "No path.\n";
  else {
    Dijkstra(source);
    Build_Dijkstra_Path(destination);
    Extend_Dijkstra();
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}