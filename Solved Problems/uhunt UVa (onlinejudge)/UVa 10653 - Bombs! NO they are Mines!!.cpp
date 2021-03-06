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
int n, m, sr, sc, dr, dc;
int delta_r[] = { -1, 0, 1, 0 };
int delta_c[] = { 0, 1, 0, -1 };
vector<vector<bool>> vis, wall;
vector<vi> layer;
bool found = 0;
queue<short> QR, QC;

void Reset() {
  wall.resize(n);
  for (int i = 0; i < n; i++)
    wall[i].assign(m, 0);
  vis.resize(n);
  for (int i = 0; i < n; i++)
    vis[i].assign(m, 0);
  layer.resize(n);
  for (int i = 0; i < n; i++)
    layer[i].assign(m, 0);
}

void BFS() {
  int r, c;
  QR.push(sr);
  QC.push(sc);
  while (!QR.empty()) {
    r = QR.front();
    QR.pop();
    c = QC.front();
    QC.pop();
    if (vis[r][c] || wall[r][c]) continue;
    if (found) return;
    vis[r][c] = 1;
    int i, j;
    for (int k = 0; k < 4; k++) {
      i = r + delta_r[k];
      j = c + delta_c[k];
      if (i >= 0 && i < n && j >= 0 && j < m) {
        layer[i][j] = layer[r][c] + 1;
        if (i == dr && j == dc) {
          found = 1;
          return;
        }
        QR.push(i);
        QC.push(j);
      }
    }
  }
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  if (!n && !m) return 0;
  Reset();
  int r, x, y, b;
  cin >> r;
  for (int i = 0; i < r; i++) {
    cin >> y >> b;
    for (int j = 0; j < b; j++) {
      cin >> x;
      wall[y][x] = 1;
    }
  }
  cin >> sr >> sc >> dr >> dc;

  return 1;
}

void Process() {
  if (sr == dr && sc == dc) {
    cout << "0\n";
    return;
  }
  while (!QR.empty()) QR.pop();
  while (!QC.empty()) QC.pop();
  found = 0;
  BFS();
  cout << layer[dr][dc] << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}