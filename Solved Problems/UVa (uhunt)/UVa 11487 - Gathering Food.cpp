#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
#define FASTIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)

const int N = 11, M = 20437, BIG = 0x3f3f3f3f;
int n, sti, stj, ct = 0;
vector<string> s;
int dp[N][N][26][505];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int mxlen, mxfood;

bool Read() {
  cin >> n;
  if (cin.eof() || n == 0)
    return 0;
  s.resize(n);
  for (int i = 0; i < n; i++)
    cin >> s[i];

  return 1;
}

int DP(int i, int j, int food, int steps) {
  if (i < 0 || j < 0 || i >= n || j >= n || steps < 0 || s[i][j] == '#')
    return 0;
  int gathered = 0;
  if (s[i][j] != '.' && s[i][j] - 'A' >= food) {
    if (s[i][j] - 'A' == mxfood) {
      if (food != mxfood)
        return 0;
      return 1;
    }
    else {
      if (food != s[i][j] - 'A')
        return 0;
      gathered++;
    }
  }
  if (dp[i][j][food][steps] != -1) 
    return dp[i][j][food][steps];
  int& ans = dp[i][j][food][steps] = 0;
  for (int k = 0; k < 4; k++)
    ans = (ans + DP(i + dr[k], j + dc[k], food + gathered, steps - 1)) % M;
  return ans;
}

void Process() {
  int ans = 0;
  cout << "Case " << ++ct << ": ";
  mxlen = 5 * n * n;
  mxfood = -1;
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (s[i][j] == 'A') {
        sti = i;
        stj = j;
      }
      if (s[i][j] != '#' && s[i][j] != '.')
        if (s[i][j] - 'A' > mxfood)
          mxfood = s[i][j] - 'A';
    }
  for (int fuel = 0; fuel <= mxlen; fuel++) {
    ans = DP(sti, stj, 0, fuel);
    if (ans > 0) {
      cout << fuel << " " << ans << "\n";
      return;
    }
  }
  cout << "Impossible\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}