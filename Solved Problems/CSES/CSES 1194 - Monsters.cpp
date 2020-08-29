#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Node {
  int depth, i, j;
};

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
char encode[4] = { 'U', 'R', 'D', 'L' };
int n, m;
char a[N][N];
vector<vector<bool>> vis;
vector<vector<char>> op;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];

  return 1;
}

void Process() {
  for (int i = 0; i < N; i++)
    a[n + 1][i] = a[i][m + 1] = '#';
  vis.assign(n + 2, vector<bool>(m + 2, 0));
  op.assign(n + 2, vector<char>(m + 2, 0));
  vii mon;
  int si, sj;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 'M')
        mon.push_back({ i, j });
      else if (a[i][j] == 'A')
        si = i, sj = j;
    }
  queue<Node> QM, Q;
  Q.push({ 0, si, sj });
  for (const ii& Mon : mon)
    QM.push({ 0, Mon.first, Mon.second });
  int ui, uj, ud, vi, vj, vd;
  ii ans = { -1, -1 };
  bool monster = 0;
  int ct = 0;
  while (!Q.empty()) {
    if (!QM.empty() && Q.front().depth >= QM.front().depth) {
      ui = QM.front().i;
      uj = QM.front().j;
      ud = QM.front().depth;
      QM.pop();
      monster = 1;
    }
    else {
      ui = Q.front().i;
      uj = Q.front().j;
      ud = Q.front().depth;
      Q.pop();
      monster = 0;
    }
    if (vis[ui][uj])
      continue;
    vis[ui][uj] = 1;
    if (monster == 0 && (ui == 1 || uj == 1 || ui == n || uj == m)) {
      ans = { ui, uj };
      break;
    }
    for (int k = 0; k < 4; k++) {
      vi = ui + dr[k];
      vj = uj + dc[k];
      if (a[vi][vj] != '.' || vis[vi][vj])
        continue;
      vd = ud + 1;
      if (monster)
        QM.push({ vd, vi, vj });
      else {
        Q.push({ vd, vi, vj });
        op[vi][vj] = encode[k];
      }
    }
  }
  if (ans.first < 0)
    cout << "NO\n";
  else {
    cout << "YES\n";
    vector<char> path;
    ii cur = ans;
    char c;
    while (1) {
      c = op[cur.first][cur.second];
      if (c == 0)
        break;
      path.push_back(c);
      if (c == 'D')
        cur.first--;
      else if (c == 'U')
        cur.first++;
      else if (c == 'L')
        cur.second++;
      else
        cur.second--;
    }
    cout << path.size() << "\n";
    for (auto it = path.rbegin(); it != path.rend(); it++)
      cout << *it;
    cout << "\n";
  }
}

int main() {
  FASTIO();

  for (int i = 0; i < N; i++)
    a[0][i] = a[i][0] = '#';

  while (Read())
    Process();

  return 0;
}