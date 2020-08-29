#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;
int n;
ll dp[18][18];
int r, rr;
int decode[256];

int main() {
  FASTIO();

  for (int i = 0; i < 10; i++)
    decode['0' + i] = i - 1;
  decode['A'] = 9;
  decode['B'] = 10;
  decode['C'] = 11;
  decode['D'] = 12;
  decode['E'] = 13;
  decode['F'] = 14;

  while (cin >> s) {
    n = s.length();
    memset(dp, 0, sizeof dp);
    if (s[0] == '?') {
      for (int i = 0; i < n; i++)
        dp[i][0] = 1;
    }
    else {
      r = decode[s[0]];
      dp[r][0] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
      if (s[i] == '?') {
        if (s[i + 1] == '?') {
          for (r = 0; r < n; r++) 
            for (rr = 0; rr < n; rr++) {
              if (abs(r - rr) < 2)
                continue;
              dp[rr][i + 1] += dp[r][i];
            }
        }
        else {
          rr = decode[s[i + 1]];
          for (r = 0; r < n; r++) {
            if (abs(r - rr) < 2)
              continue;
            dp[rr][i + 1] += dp[r][i];
          }
        }
      }
      else {
        r = decode[s[i]];
        if (s[i + 1] == '?') {
          for (rr = 0; rr < n; rr++) {
            if (abs(r - rr) < 2)
              continue;
            dp[rr][i + 1] += dp[r][i];
          }
        }
        else {
          rr = decode[s[i + 1]];
          if (abs(r - rr) >= 2) 
            dp[rr][i + 1] += dp[r][i];
        }
      }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++)
      ans += dp[i][n - 1];
    cout << ans << "\n";

    if (cin.eof())
      break;
  }

  return 0;
}