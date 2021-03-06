#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <float.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 25, K = 206, M = 1002;

int ct = 0;
int n, nn, cash, x, k, kk, p[K], f[K][N];
double dp[K][M][N], t;

bool Read() {
  cin >> n >> x >> t >> k;
  if (!n && !x && !t && !k) return 0;
  for (int i = 1; i <= k; i++) {
    cin >> p[i];
    p[i + k] = p[i];
    for (int j = 1; j <= n + 1; j++) {
      cin >> f[i][j];
      f[i + k][j] = f[i][j];
    }
  }

  return 1;
}

void DP() {
  double avg;
  memset(dp[0], 0., sizeof dp[0]);
  for (int i = 1; i <= kk; i++) {
    for (int j = 1; j <= cash; j++) {
      for (int k = 0; k <= nn; k++) {
        dp[i][j][k] = dp[i - 1][j][k];
        if (j >= p[i] && k) {
          avg = 0;
          for (int l = 1; l <= n + 1; l++)
            avg += f[i][l];
          avg /= (n + 1);
          dp[i][j][k] = max(dp[i][j][k], avg + dp[i - 1][j - p[i]][k - 1]);
        }
      }
    }
  }
}

void Process() {
  nn = 2 * (n + 1);
  kk = 2 * k;
  cash = floor(((double)x * (double)(n + 1) - 1.1 * (n + 1) * t) / 1.0999 + DBL_EPSILON);
  DP();
  cout << fixed << setprecision(2) << dp[kk][cash][nn] << "\n";
  
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}