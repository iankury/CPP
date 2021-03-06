#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 12, M = 4111, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, beepers, dp[N][M];

struct Point {
  int x, y;
  bool operator == (const Point& p) const {
    return x == p.x && y == p.y;
  }
};
Point a[N];

int D(int p, int q) {
  return abs(a[p].x - a[q].x) + abs(a[p].y - a[q].y);
}

int DP(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  int& ans = dp[i][j];
  ans = BIG;
  if (!j) ans = D(0, i);
  else 
    for (int k = 0; k <= beepers; k++) 
      if (j & (1 << k)) 
        ans = min(ans, D(k, i) + DP(k, j - (1 << k)));
  return ans;
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m >> a[0].x >> a[0].y >> beepers;
  for (int i = 1; i <= beepers; i++)
    cin >> a[i].x >> a[i].y;

  return 1;
}

void Process() {
  memset(dp, -1, sizeof dp);
  cout << "The shortest path has length " << DP(0, (1 << (beepers + 1)) - 1) << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}