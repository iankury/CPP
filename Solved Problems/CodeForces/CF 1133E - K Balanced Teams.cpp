#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int n, k;
vi a;
vector<vi> dp;

int DP(int i, int j) {
  if (i >= n || j <= 0)
    return 0;

  int& ans = dp[i][j];

  if (ans == -1) {
    int ix = i;
    for (; ix < n && a[ix] - a[i] < 6; ix++);
    ans = max(ix - i + DP(ix, j - 1), DP(i + 1, j));
  }

  return ans;
}

void Solve() {
  sort(begin(a), end(a));
  dp.assign(n, vi(k + 1, -1));
  cout << DP(0, k) << "\n";
}

int main() {
  io();

  while (cin >> n) {
    cin >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) 
      cin >> a[i];
    Solve();
  }

  return 0;
}