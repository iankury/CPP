#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, forbidden;
char ans[N][N];
bool a[N][N], vis[2][N], b;

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];

  return 1;
}

void DFS(int u) {
  if (u == forbidden) return;
  vis[b][u] = 1;
  for (int v = 0; v < n; v++)
    if (a[u][v] && !vis[b][v])
      DFS(v);
}

void Process() {
  forbidden = -1;
  memset(ans, 'N', sizeof ans);
  memset(vis[0], 0, sizeof vis[0]);
  cout << "Case " << ++ct << ":\n";
  b = 0;
  DFS(0);
  b = 1;
  for (forbidden = 0; forbidden < n; forbidden++) {
    memset(vis[1], 0, sizeof vis[1]);
    DFS(0);
    for (int v = 0; v < n; v++)
      if (vis[0][v] && !vis[1][v])
        ans[forbidden][v] = 'Y';
  }
  string separator = "+";
  separator.append(string(2 * n - 1, '-'));
  separator.push_back('+');
  for (int i = 0; i < n; i++) {
    cout << separator << "\n";
    for (int j = 0; j < n; j++) {
      if (!j) cout << "|";
      cout << ans[i][j] << "|";
    }
    cout << "\n";
  }
  cout << separator << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}