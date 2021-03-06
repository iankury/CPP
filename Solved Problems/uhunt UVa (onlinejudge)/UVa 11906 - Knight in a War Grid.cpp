#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, r, c, m, a[N][N], w, even, odd;
bool vis[N][N];

bool Read() {
  memset(a, 0, sizeof a);
  cin >> r;
  if (cin.eof()) return 0;
  cin >> c >> m >> n >> w;
  int t1, t2;
  for (int i = 0; i < w; i++) {
    cin >> t1 >> t2;
    a[t1][t2] = 1;
  }
  return 1;
}

queue<ii> Q;

bool In_Bounds(int p, int q) {
  return p >= 0 && q >= 0 && p < r && q < c;
}

void BFS() {
  Q.push({ 0, 0 });
  while (!Q.empty()) {
    int i = Q.front().first, j = Q.front().second;
    Q.pop();
    if (vis[i][j] || a[i][j]) continue;
    vis[i][j] = 1;
    vii cands = { {i + m, j + n}, {i + n, j + m},
    {i + m, j - n}, {i - n, j + m},
    {i + n, j - m}, {i - m, j + n},
    {i - m, j - n}, {i - n, j - m} };
    set<ii> no_repeat;
    for (auto cand : cands) no_repeat.insert(cand);
    int ans = 0;
    for (auto cand : no_repeat) {
      int p = cand.first, q = cand.second;
      if (In_Bounds(p, q)) {
        if (a[p][q]) continue;
        ans++;
        Q.push(cand);
      }
    }
    if (ans % 2) odd++;
    else even++;
  }
}

void Process() {
  even = odd = 0;
  memset(vis, 0, sizeof vis);
  BFS();
  cout << "Case " << ++ct << ": " << even << " " << odd << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}