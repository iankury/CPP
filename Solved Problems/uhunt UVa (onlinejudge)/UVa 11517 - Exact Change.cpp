#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 20008, BIG = 0x3f3f3f3f;

int ct = 0;
int s, n, a[N], dp[N][M];

bool Read() {
  cin >> s;
  if (cin.eof()) return 0;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  return 1;
}

int DP(int i, int j) {
  if (!i && j) return BIG;
  if (dp[i][j] != -1) return dp[i][j];
  int& ans = dp[i][j];
  ans = DP(i - 1, j);
  if (j >= a[i]) ans = min(ans, 1 + DP(i - 1, j - a[i]));
  return ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  for (int i = 0; i <= n; i++) dp[i][0] = 0;
  int ans_n = 0, ans_sum = 0;
  for (int j = s; j < M - 1; j++) {
    ans_n = DP(n, j);
    if (ans_n != BIG) {
      ans_sum = j;
      break;
    }
  }
  cout << ans_sum << " " << ans_n << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}