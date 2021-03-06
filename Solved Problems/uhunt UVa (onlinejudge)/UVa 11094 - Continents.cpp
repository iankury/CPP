#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 21, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, st_r, st_c;
char land = 'l', water = 'w', a[N][N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  int i, j;
  cin >> st_r >> st_c;

  return 1;
}

int Flood_Fill(int i, int j) {
  if (a[i][j] != land) return 0;
  a[i][j] = water;
  int ans = 1;
  if (i) ans += Flood_Fill(i - 1, j);
  if (i < n - 1) ans += Flood_Fill(i + 1, j);
  int left = j - 1, right = j + 1;
  if (left < 0) left = m - 1;
  if (right >= m) right = 0;
  ans += Flood_Fill(i, left);
  ans += Flood_Fill(i, right);
  return ans;
}

void Process() {
  land = a[st_r][st_c];
  water = land > 100 ? land - 1 : land + 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] != land) {
        water = a[i][j];
        break;
      }
  Flood_Fill(st_r, st_c);
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      int area = Flood_Fill(i, j);
      ans = max(ans, area);
    }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}