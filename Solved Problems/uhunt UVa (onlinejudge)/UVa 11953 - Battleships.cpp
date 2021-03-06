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

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, dr[] = { -1, 0, 1, 0 }, dc[] = { 0, 1, 0, -1 };
char a[N][N];
const char water = '.', ship = 'x';

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];

  return 1;
}

bool In_Bounds(int i, int j) {
  return i >= 0 && j >= 0 && i < n && j < n;
}

void Flood_Fill(int i, int j) {
  if (In_Bounds(i, j) && a[i][j] != water) {
    a[i][j] = water;
    for (int ix = 0; ix < 4; ix++)
      Flood_Fill(i + dr[ix], j + dc[ix]);
  }
}

void Process() {
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] == ship) {
        ans++;
        Flood_Fill(i, j);
      }
  cout << "Case " << ++ct << ": " << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}