#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 55, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, si, sj, di, dj, sdir, a[N][N];
bool vis[N][N][4];
map<string, int> encode{ {"north", 0}, {"east", 1}, {"south", 2}, {"west", 3} };

struct State {
  int y, x, dir;
  bool operator != (const State& p) const {
    return y != p.y || x != p.x || dir != p.dir;
  }
};
State pi[N][N][4];
const State NIL = { -1, -1, -1 };

State TR(const State& state) {
  State ans = state;
  ans.dir++;
  if (ans.dir > 3) ans.dir = 0;
  return ans;
}

State TL(const State& state) {
  State ans = state;
  ans.dir--;
  if (ans.dir < 0) ans.dir = 3;
  return ans;
}

State GO(const State& state, int d) {
  State ans = state;
  if (state.dir == 0) ans.y -= d;
  else if (state.dir == 1) ans.x += d;
  else if (state.dir == 2) ans.y += d;
  else ans.x -= d;
  return ans;
}

bool In_Bounds(int i, int j) {
  return i > 0 && i < n && j > 0 && j < m;
}

bool Free(const State& p, int d) {
  if (p.dir == 0) {
    if (!In_Bounds(p.y - d, p.x))
      return 0;
    for (int i = 1; i <= d; i++)
      if (a[p.y - i][p.x])
        return 0;
    return 1;
  }
  else if (p.dir == 1) {
    if (!In_Bounds(p.y, p.x + d))
      return 0;
    for (int i = 1; i <= d; i++)
      if (a[p.y][p.x + i])
        return 0;
    return 1;
  }
  else if (p.dir == 2) {
    if (!In_Bounds(p.y + d, p.x))
      return 0;
    for (int i = 1; i <= d; i++)
      if (a[p.y + i][p.x])
        return 0;
    return 1;
  }
  else {
    if (!In_Bounds(p.y, p.x - d))
      return 0;
    for (int i = 1; i <= d; i++)
      if (a[p.y][p.x - i])
        return 0;
    return 1;
  }
  return 1;
}

bool Read() {
  cin >> n >> m;
  if (!n && !m) return 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  string s;
  cin >> si >> sj >> di >> dj >> s;
  sdir = encode[s];

  return 1;
}

void Process() {
  memset(vis, 0, sizeof vis);
  pi[si][sj][sdir] = NIL;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] == 1) {
        if (!a[i + 1][j]) a[i + 1][j] = 2;
        if (!a[i][j + 1]) a[i][j + 1] = 2;
        if (!a[i + 1][j + 1]) a[i + 1][j + 1] = 2;
      }
  queue<State> Q;
  vis[si][sj][sdir] = 1;
  Q.push({ si, sj, sdir });
  while (!Q.empty()) {
    State cur = Q.front();
    Q.pop();
    if (cur.y == di && cur.x == dj) {
      int ans = 0;
      while (pi[cur.y][cur.x][cur.dir] != NIL) {
        cur = pi[cur.y][cur.x][cur.dir];
        ans++;
      }
      cout << ans << "\n";
      return;
    }
    State p = TL(cur), q = TR(cur);
    if (!vis[p.y][p.x][p.dir]) {
      pi[p.y][p.x][p.dir] = cur;
      vis[p.y][p.x][p.dir] = 1;
      Q.push(p);
    }
    if (!vis[q.y][q.x][q.dir]) {
      pi[q.y][q.x][q.dir] = cur;
      vis[q.y][q.x][q.dir] = 1;
      Q.push(q);
    }
    for (int i = 3; i > 0; i--) {
      State v = GO(cur, i);
      if (Free(cur, i) && !vis[v.y][v.x][v.dir]) {
        pi[v.y][v.x][v.dir] = cur;
        vis[v.y][v.x][v.dir] = 1;
        Q.push(v);
      }
    }
  }
  cout << "-1\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}