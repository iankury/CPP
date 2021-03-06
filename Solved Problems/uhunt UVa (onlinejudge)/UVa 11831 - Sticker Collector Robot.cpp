#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 115, S = 50005, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, s, row, col;
char a[N][N];
enum { UP, RIGHT, DOWN, LEFT };
int dir;
string cmd;

void Turn_Right() { dir = (dir + 1) % 4; }
void Turn_Left() { dir--; if (dir < 0) dir = 3; }
void Setup() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (isalpha(a[i][j])) {
        row = i;
        col = j;
        if (a[i][j] == 'N') dir = UP;
        else if (a[i][j] == 'S') dir = DOWN;
        else if (a[i][j] == 'L') dir = RIGHT;
        else dir = LEFT;
      }
}

bool Read() {
  cin >> n >> m >> s;
  if (!n && !m && !s) return 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  cin >> cmd;

  return 1;
}

void Process() {
  for (int i = 0; i < n + 3; i++)
    a[i][0] = a[i][m + 1] = '#';
  for (int j = 0; j < m + 3; j++)
    a[0][j] = a[n + 1][j] = '#';
  Setup();
  int ans = 0;
  for (int i = 0; i < s; i++) {
    if (cmd[i] == 'D') Turn_Right();
    else if (cmd[i] == 'E') Turn_Left();
    else {
      if (dir == UP && a[row - 1][col] != '#') row--;
      else if (dir == RIGHT && a[row][col + 1] != '#') col++;
      else if (dir == DOWN && a[row + 1][col] != '#') row++;
      else if (dir == LEFT && a[row][col - 1] != '#') col--;
      if (a[row][col] == '*') {
        a[row][col] = '.';
        ans++;
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}