#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef vector<double> vd;

vd Transition(const vd& previous_state) {
  const int n = previous_state.size();
  vd next_state(n);

  for (int i = 0; i < n; i++)
    if (previous_state[i]) {
      const double p = previous_state[i] / 6.;
      for (int j = i + 1; j <= i + 6 && j < n; j++)
        next_state[j] += p;
    }

  return next_state;
}

int main() {
  io();

  int n, a, b;
  cin >> n >> a >> b;

  vd dp(6 * n + 1);
  dp[0] = 1;

  while (n--)
    dp = Transition(dp);

  double ans = 0;
  for (int i = a; i <= b; i++)
    ans += dp[i];
  cout << fixed << setprecision(6) << ans << "\n";

  return 0;
}