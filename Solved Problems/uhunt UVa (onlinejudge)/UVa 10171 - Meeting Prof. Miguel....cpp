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

const int N = 27, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[2][N][N];
char st, en;

bool Read() {
  cin >> n;
  if (cin.eof() || !n)
    return 0;
  char u, v, y, dir;
  int w;
  memset(a, BIG, sizeof a);
  for (int i = 0; i < n; i++) {
    cin >> y >> dir >> u >> v >> w;
    a[y == 'Y'][u - 'A'][v - 'A'] = w;
    if (dir == 'B')
      a[y == 'Y'][v - 'A'][u - 'A'] = w;
  }
  cin >> st >> en;

  return 1;
}

void Process() {
  int ans = BIG, mn_i;
  for (int y = 0; y < 2; y++)
    for (int i = 0; i < 26; i++)
      a[y][i][i] = 0;
  for (int y = 0; y < 2; y++)
    for (int k = 0; k < 26; k++)
      for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
          if (i != j)
            a[y][i][j] = min(a[y][i][j], a[y][i][k] + a[y][k][j]);
  vector<char> places;
  for (int i = 0; i < 26; i++) {
    int sum = a[1][st - 'A'][i] + a[0][en - 'A'][i];
    if (ans > sum) {
      ans = sum;
      places.clear();
      places.push_back((char)(i + 'A'));
    }
    else if (ans == sum)
      places.push_back((char)(i + 'A'));
  }
  if (ans == BIG)
    cout << "You will never meet.\n";
  else {
    cout << ans;
    for (char c : places)
      cout << " " << c;
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}