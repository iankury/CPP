#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
char a[N][N];
int sz[N][N];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
ii root[N][N];
vector<vector<bool>> vis;
ii cur_root;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  vis.assign(n + 2, vector<bool>(m + 2, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];

  return 1;
}

void Flood(int i, int j) {
  if (vis[i][j] || a[i][j] != '.')
    return;
  vis[i][j] = 1;
  root[i][j] = cur_root;
  sz[cur_root.first][cur_root.second]++;
  for (int k = 0; k < 4; k++) 
    Flood(i + dr[k], j + dc[k]);
}

void Process() {
  int ix, jx, ans;
  for (int i = 0; i < max(n, m) + 2; i++)
    a[n + 1][i] = a[i][m + 1] = '!';
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) 
      if (!vis[i][j]) {
        cur_root = { i, j };
        sz[i][j] = 0;
        Flood(i, j);
      }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == '.')
        cout << '.';
      else {
        ans = 1;
        set<ii> S;
        for (int k = 0; k < 4; k++)
          if (a[i + dr[k]][j + dc[k]] == '.') {
            ix = root[i + dr[k]][j + dc[k]].first;
            jx = root[i + dr[k]][j + dc[k]].second;
            if (!S.count({ ix,jx })) {
              ans += sz[ix][jx];
              S.insert({ ix, jx });
            }
          }
        cout << ans % 10;
      }
    }
    cout << "\n";
  }
}

int main() {
  FASTIO();

  for (int i = 0; i < N; i++)
    a[0][i] = a[i][0] = '!';

  while (Read())
    Process();

  return 0;
}