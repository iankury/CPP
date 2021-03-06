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

const int N = 15, M = 4100, BIG = 0x3f3f3f3f;

int ct = 0;
int m, n, k, t, a[N][N];
bool vis[N][N][M];

struct State { int y, x, unlocked, step; };
struct Move { int y, x; };
Move moves[N];
int st_unlocked;

bool Read() {
  cin >> m;
  if (cin.eof())
    return 0;
  cin >> n >> k >> t;
  if (!m && !n && !k && !t)
    return 0;
  for (int i = 1; i <= k; i++) 
    cin >> moves[i].x >> moves[i].y;
  int p;
  st_unlocked = 0;
  for (int i = 0; i < t; i++) {
    cin >> p;
    st_unlocked += (1 << (p - 1));
  }
  for (int i = m - 1; i >= 0; i--)
    for (int j = 0; j < n; j++) 
      cin >> a[i][j];

  return 1;
}

void Process() {
  memset(vis, 0, sizeof vis);
  cout << "Case #" << ++ct << ": ";
  queue<State> Q;
  Q.push({ 0, 0, st_unlocked, 0 });
  State cur;
  while (!Q.empty()) {
    cur = Q.front();
    Q.pop();
    if (vis[cur.y][cur.x][cur.unlocked])
      continue;
    if (cur.y == m - 1 && cur.x == n - 1) {
      cout << cur.step << "\n";
      return;
    }
    int dl = a[cur.y][cur.x];
    cur.step++;
    vis[cur.y][cur.x][cur.unlocked] = 1;
    if (dl && !(cur.unlocked & (1 << dl - 1))) 
      Q.push({ cur.y, cur.x, cur.unlocked | (1 << dl - 1), cur.step });
    for (int i = 0; i < 12; i++) {
      if (cur.unlocked & (1 << i)) {
        Move move = moves[i + 1];
        State newpos = { cur.y + move.y, cur.x + move.x, cur.unlocked, cur.step };
        if (newpos.y >= 0 && newpos.y < m && newpos.x >= 0 && newpos.x < n)
          Q.push(newpos);
      }
    }
  }
  
  cout << "-1\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}