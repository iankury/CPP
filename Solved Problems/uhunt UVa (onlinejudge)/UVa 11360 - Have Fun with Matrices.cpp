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

const int N = 11, M = 51, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, a[N][N], b[N][N], p[M], q[M];
char c[N][N];
string s[M];

bool Read() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      cin >> c[i][j];
      a[i][j] = c[i][j] - '0';
    }
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> s[i];
    if (s[i][0] == 'r' || s[i][0] == 'c') 
      cin >> p[i] >> q[i];
  }
  return 1;
}

void Swap(int& px, int& qx) {
  int temp = px;
  px = qx;
  qx = temp;
}

void Process() {
  cout << "Case #" << ++ct << "\n";
  for (int k = 0; k < m; k++) {
    if (s[k][0] == 'r')
      for (int j = 1; j <= n; j++)
        Swap(a[p[k]][j], a[q[k]][j]);
    else if (s[k][0] == 'c')
      for (int i = 1; i <= n; i++)
        Swap(a[i][p[k]], a[i][q[k]]);
    else if (s[k][0] == 'i')
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          a[i][j] = (a[i][j] + 1) % 10;
    else if (s[k][0] == 'd')
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          a[i][j] = (a[i][j] + 9) % 10;
    else {
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          b[i][j] = a[i][j];
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          a[i][j] = b[j][i];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << a[i][j];
    cout << "\n";
  }
  cout << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}