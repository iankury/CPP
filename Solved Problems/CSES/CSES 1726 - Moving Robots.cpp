#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
double dp[8][8][101][64];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

void Build_DP() {
  memset(dp, 0, sizeof dp);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      dp[i][j][0][i * 8 + j] = 1;
  int ix, jx;
  double choices, cur;
  for (int k = 0; k < 100; k++)
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        vi pi, pj;
        for (int neib = 0; neib < 4; neib++) {
          ix = i + dr[neib];
          if (ix < 0 || ix > 7)
            continue;
          jx = j + dc[neib];
          if (jx < 0 || jx > 7)
            continue;
          pi.push_back(ix);
          pj.push_back(jx);
        }
        choices = pi.size();
        for (int r = 0; r < 64; r++) {
          cur = dp[i][j][k][r];
          if (cur == 0.)
            continue;
          for (int neib = 0; neib < pi.size(); neib++) {
            ix = pi[neib];
            jx = pj[neib];
            double& nx = dp[ix][jx][k + 1][r];
            nx += cur / choices;
          }
        }
      }
}

void Process() {
  double ans = 0, cur;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      cur = 1.;
      for (int r = 0; r < 64; r++)
        cur *= 1. - dp[i][j][n][r];
      ans += cur;
    }

  cout << fixed << setprecision(6) << ans << "\n";
}

int main() {
  FASTIO();

  Build_DP();

  while (cin >> n) {
    Process();

    if (cin.eof())
      break;
  }

  return 0;
}