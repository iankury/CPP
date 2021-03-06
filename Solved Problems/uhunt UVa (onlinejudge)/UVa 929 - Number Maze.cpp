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
int n, m;
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int a[N][N];
vector<vi> dist;

bool In_Bounds(int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}

struct Node {
  int r, c, d;
  bool operator < (const Node& p) const {
    return d > p.d;
  }
};

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];

  return 1;
}

void Process() {
  dist.assign(n, vi(m, BIG));
  dist[0][0] = a[0][0];
  priority_queue<Node> Q;
  Q.push({ 0, 0, a[0][0] });
  Node u, v;
  while (!Q.empty()) {
    u = Q.top();
    Q.pop();
    for (int i = 0; i < 4; i++) {
      v = { u.r + dr[i], u.c + dc[i], 0 };
      if (!In_Bounds(v.r, v.c))
        continue;
      v.d = u.d + a[v.r][v.c];
      if (v.d < dist[v.r][v.c]) {
        Q.push(v);
        dist[v.r][v.c] = v.d;
      }
    }
  }
  cout << dist[n - 1][m - 1] << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}