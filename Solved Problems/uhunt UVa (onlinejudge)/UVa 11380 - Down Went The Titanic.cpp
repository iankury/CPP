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

const int N = 32, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int x, y, p;
char a[N][N];
int n, m, s, t;
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
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
  cin >> x;
  if (cin.eof())
    return 0;
  cin >> y >> p;
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      cin >> a[i][j];

  return 1;
}

bool In_Bounds(int i, int j) {
  return i >= 0 && i < x && j >= 0 && j < y;
}

void Process() {
  n = x * y * 2 + 8;
  s = n - 3;
  t = n - 2;
  int offset = x * y + 1;
  adj.assign(n + 1, vector<Edge>());
  int u, v, cap;
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++) {
      if (a[i][j] == '~')
        continue;
      u = i * y + j;
      cap = 9999;
      if (a[i][j] == '.') {
        Add(u, u + offset, 1);
        u += offset;
        cap = 1;
      }
      else if (a[i][j] == '*') 
        Add(s, u, 1);
      else if (a[i][j] == '#')
        Add(u, t, p);
      for (int k = 0; k < 4; k++) {
        int ix = i + dr[k];
        int jx = j + dc[k];
        if (In_Bounds(ix, jx) && a[ix][jx] != '~' && a[ix][jx] != '*') {
          v = ix * y + jx;
          Add(u, v, cap);
        }
      }
    }
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