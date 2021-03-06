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

const int N = 333, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, dr[] = { -1, 0, 1, 0 }, dc[] = { 0, 1, 0, -1 };
string Hex_To_Bin[256];
char a[N][N];
char Translate[] = { 'W', 'A', 'K', 'J', 'S', 'D' };

void Initialize_Hex_To_Bin() {
  Hex_To_Bin['0'] = "0000";
  Hex_To_Bin['1'] = "0001";
  Hex_To_Bin['2'] = "0010";
  Hex_To_Bin['3'] = "0011";
  Hex_To_Bin['4'] = "0100";
  Hex_To_Bin['5'] = "0101";
  Hex_To_Bin['6'] = "0110";
  Hex_To_Bin['7'] = "0111";
  Hex_To_Bin['8'] = "1000";
  Hex_To_Bin['9'] = "1001";
  Hex_To_Bin['a'] = "1010";
  Hex_To_Bin['b'] = "1011";
  Hex_To_Bin['c'] = "1100";
  Hex_To_Bin['d'] = "1101";
  Hex_To_Bin['e'] = "1110";
  Hex_To_Bin['f'] = "1111";
}

bool Read() {
  cin >> n >> m;
  if (!n && !m) return 0;
  char c;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> c;
      for (int k = 0; k < 4; k++)
        a[i][4 * j + k] = Hex_To_Bin[c][k];
    }
  m *= 4;

  return 1;
}

struct Point {
  int row, col;
};

bool In_Bounds(Point p) {
  return p.row >= 0 && p.row < n && p.col >= 0 && p.col < m;
}

Point Find_Outside_Pixel() {
  for (int i = 0; i < n; i++) {
    if (a[i][0] == '0')
      return { i, 0 };
    if (a[i][m - 1] == '0')
      return { i, m - 1 };
  }
  for (int j = 0; j < m; j++) {
    if (a[0][j] == '0')
      return { 0, j };
    if (a[n - 1][j] == '0')
      return { n - 1, j };
  }
  return { -1, -1 };
}

queue<Point> yard_candidates;

int Flood_Fill(char land, char water, Point tile) {
  if (!In_Bounds(tile)) return 0;
  if (a[tile.row][tile.col] == land) {
    a[tile.row][tile.col] = water;
    int ans = 1;
    for (int i = 0; i < 4; i++)
      ans += Flood_Fill(land, water, { tile.row + dr[i], tile.col + dc[i] });
    return ans;
  }
  else if (water == '3' && a[tile.row][tile.col] == '0')
    yard_candidates.push(tile);
  return 0;
}

Point Find_Glyph(int line) {
  for (int i = line; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] == '1')
        return { i, j };
  return { -1, -1 };
}

vector<char> ans;

void Process() {
  cout << "Case " << ++ct << ": ";
  Point outside = Find_Outside_Pixel();
  while (outside.row != -1) {
    Flood_Fill('0', '2', outside);
    outside = Find_Outside_Pixel();
  }
  Point start = Find_Glyph(0);
  ans.clear();
  while (start.row != -1) {
    Flood_Fill('1', '3', start);
    int yards = 0;
    while (!yard_candidates.empty()) {
      int area = Flood_Fill('0', '4', yard_candidates.front());
      yard_candidates.pop();
      if (area) yards++;
    }
    ans.push_back(Translate[yards]);
    start = Find_Glyph(start.row);
  }
  sort(ans.begin(), ans.end());
  for (char c : ans) cout << c;
  cout << "\n";
}

int main() {
  FASTIO();
  Initialize_Hex_To_Bin();

  while (Read()) Process();

  return 0;
}