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

const int N = 11, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N][N];

bool Read() {
  cin >> a[0][0];
  if (cin.eof()) return 0;
  cin >> a[2][0] >> a[2][2];
  cin >> a[4][0] >> a[4][2] >> a[4][4];
  cin >> a[6][0] >> a[6][2] >> a[6][4] >> a[6][6];
  cin >> a[8][0] >> a[8][2] >> a[8][4] >> a[8][6] >> a[8][8];

  return 1;
}

void Process() {
  for (int i = 1; i < 8; i += 2) a[8][i] = (a[6][i - 1] - a[8][i - 1] - a[8][i + 1]) / 2;
  for (int i = 7; i; i--) for (int j = 0; j < 8; j++) a[i][j] = a[i + 1][j] + a[i + 1][j + 1];
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j <= i; j++) {
      if (j) cout << " ";
      cout << a[i][j];
    }
    cout << "\n";
  }
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}