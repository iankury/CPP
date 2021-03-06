#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n_floes;
double range;
int n, m, s, t, offset;
vi level, st_from;

struct Edge;
vector<vector<Edge>> adj, bkp;
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

struct Point {
  int x, y;
};

struct Floe {
  Point coor;
  int penguins, durability;
};
vector<Floe> floes;

double Distance(const Point& p, const Point& q) {
  return sqrt((double)(p.x - q.x) * (double)(p.x - q.x) 
    + (double)(p.y - q.y) * (double)(p.y - q.y));
}

int Dinitz() {
  int maxflow = 0, curflow;
  while (BFS()) {
    st_from.assign(n + 1, 0);
    while (1) {
      curflow = DFS(s, BIG);
      if (!curflow)
        break;
      maxflow += curflow;
    }
  }
  return maxflow;
}

bool Read() {
  cin >> n_floes;
  if (cin.eof())
    return 0;
  cin >> range;
  floes.resize(n_floes);
  for (int i = 0; i < n_floes; i++)
    cin >> floes[i].coor.x >> floes[i].coor.y >> floes[i].penguins >> floes[i].durability;

  return 1;
}

void Process() {
  offset = n_floes + 5;
  n = offset * 2 + 5;
  s = n - 3;
  t = n - 2;
  adj.assign(n + 2, vector<Edge>());
  int total_penguins = 0;
  for (int i = 0; i < n_floes; i++) {
    if (floes[i].penguins) {
      Add(s, i, floes[i].penguins);
      total_penguins += floes[i].penguins;
    }
    Add(i, i + offset, floes[i].durability);
    for (int j = 0; j < n_floes; j++)
      if (i != j) {
        if (Distance(floes[i].coor, floes[j].coor) <= range)
          Add(i + offset, j, BIG);
      }
  }
  vi ans;
  bkp = adj;
  for (int i = 0; i < n_floes; i++) {
    Add(i, t, BIG);
    int maxflow = Dinitz();
    if (maxflow == total_penguins)
      ans.push_back(i);
    adj = bkp;
  }
  if (ans.empty())
    cout << "-1\n";
  else {
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
      cout << " " << ans[i];
    cout << "\n";
  }
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}