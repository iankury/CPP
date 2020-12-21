#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200, M = 1000000007, BIG = 0x3f3f3f3f;
const ll MAXINT = 2147483647;

int n;
string s;
ll dp[N];

bool Read() {
  cin >> s;
  n = s.length();

  return 1;
}

ll DP(int r) {
  if (dp[r] != -1)
    return dp[r];
  ll ans = 0, cur = 0, mul = 1;
  for (int i = 0; i < 11 && r - i >= 0; i++, mul *= 10) {
    cur += (ll)(s[r - i] - '0') * mul;
    if (cur > MAXINT)
      break;
    ans = max(ans, cur + (r - i == 0 ? 0 : DP(r - i - 1)));
  }
  return dp[r] = ans;
}

void Process() {
  memset(dp, -1, sizeof dp);
  cout << DP(n - 1) << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}