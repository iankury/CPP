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

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N][N], rings;
vi c[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  rings = (n + 1) / 2;
  int temp;
  for (int i = 0; i < rings; i++) {
    cin >> temp;
    c[i].resize(temp);
    for (int j = 0; j < temp; j++) cin >> c[i][j];
  }

  return 1;
}

void Swap(int& p, int& q) {
  int temp = p;
  p = q;
  q = temp;
}

void Process() {
  for (int k = 0; k < rings; k++) {
    for (int l = 0; l < c[k].size(); l++) {
      if (c[k][l] == 1) {
        for (int j = k; j < n - k; j++) Swap(a[k][j], a[n - 1 - k][j]);
        for (int i = k + 1; i < n / 2; i++) {
          Swap(a[i][k], a[n - 1 - i][k]);
          Swap(a[i][n - 1 - k], a[n - 1 - i][n - 1 - k]);
        }
      }
      else if (c[k][l] == 2) {
        for (int i = k; i < n - k; i++) Swap(a[i][k], a[i][n - 1 - k]);
        for (int j = k + 1; j < n / 2; j++) {
          Swap(a[k][j], a[k][n - 1 - j]);
          Swap(a[n - 1 - k][j], a[n - 1 - k][n - 1 - j]);
        }
      }
      else if (c[k][l] == 3) {
        for (int j = k + 1; j < n - k - 1; j++) {
          Swap(a[k][j], a[j][k]);
          Swap(a[n - 1 - k][j], a[j][n - 1 - k]);
        }
        Swap(a[n - 1 - k][k], a[k][n - 1 - k]);
      }
      else {
        for (int j = k + 1; j < n - k - 1; j++) {
          Swap(a[k][j], a[n - 1 - j][n - 1 - k]);
          Swap(a[n - 1 - k][j], a[n - 1 - j][k]);
        }
        Swap(a[k][k], a[n - 1 - k][n - 1 - k]);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
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