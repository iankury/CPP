#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, Q = 100005, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, q, r[Q], c[Q], ans[N][N];
ii root[N][N];
char a[N][N];
vector<vector<bool>> vis;
ii cur_root;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m >> q;
  vis.assign(n + 1, vector<bool>(m + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  for (int i = 0; i < q; i++)
    cin >> r[i] >> c[i];

  return 1;
}

void Flood(int ix, int jx) {
  if (vis[ix][jx])
    return;
  vis[ix][jx] = 1;
  root[ix][jx] = cur_root;
  for (int i = 0; i < 4; i++) {
    if (a[ix + dr[i]][jx + dc[i]] == '.')
      Flood(ix + dr[i], jx + dc[i]);
    else if (a[ix + dr[i]][jx + dc[i]] == '*') 
      ans[cur_root.first][cur_root.second]++;
  }
}

void Process() {
  for (int i = 0; i < max(n, m) + 2; i++)
    a[n + 1][i] = a[i][m + 1] = '!';
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j] == '.' && !vis[i][j]) {
        ans[i][j] = 0;
        cur_root = { i, j };
        Flood(i, j);
      }
  int ix, jx;
  for (int i = 0; i < q; i++) {
    ix = root[r[i]][c[i]].first;
    jx = root[r[i]][c[i]].second;
    cout << ans[ix][jx] << "\n";
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