#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 102, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, r, c, k, a[N][N][2], who;
bool turn;

bool Read() {
  cin >> n >> r >> c >> k;
  if (!n && !k && !r && !k) return 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      cin >> a[i][j][0];
  return 1;
}

bool In_Bounds(int i, int j) {
  return i >= 0 && i < r && j >= 0 && j < c;
}

void Conquer(int i, int j) {
  if (In_Bounds(i, j))
    if (a[i][j][turn] == who + 1 || (!a[i][j][turn] && who == n - 1)) 
      a[i][j][!turn] = who;
}

void Process() {
  turn = 0;
  for (int cn = 0; cn < k; cn++, turn = !turn) {
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        a[i][j][!turn] = a[i][j][turn];
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++) {
        who = a[i][j][turn];
        Conquer(i + 1, j);
        Conquer(i - 1, j);
        Conquer(i, j + 1);
        Conquer(i, j - 1);
      }
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (j) cout << " ";
      cout << a[i][j][turn];
    }
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}