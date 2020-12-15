#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int R, G, B;
vi r, g, b;
vector<vector<vector<ll>>> dp;

ll DP(int i, int j, int k) {
  if (int(!i) + int(!j) + int(!k) > 1)
    return 0;
  
  ll& ans = dp[i][j][k];

  if (ans == -1) {
    if (!i)
      ans = DP(i, j - 1, k - 1) + g[j] * b[k];
    else if (!j)
      ans = DP(i - 1, j, k - 1) + r[i] * b[k];
    else if (!k)
      ans = DP(i - 1, j - 1, k) + r[i] * g[j];
    else {
      ans = DP(i, j - 1, k - 1) + g[j] * b[k];
      ans = max(ans, DP(i - 1, j, k - 1) + r[i] * b[k]);
      ans = max(ans, DP(i - 1, j - 1, k) + r[i] * g[j]);
    }
  }

  return ans;
}

void Solve() {
  dp.assign(R, vector<vector<ll>>(G, vector<ll>(B, -1)));

  sort(begin(r) + 1, end(r));
  sort(begin(g) + 1, end(g));
  sort(begin(b) + 1, end(b));
  cout << DP(R - 1, G - 1, B - 1) << "\n";
}

int main() {
  io();

  while (cin >> R) {
    cin >> G >> B;
    R++; G++; B++;
    r.resize(R);
    g.resize(G);
    b.resize(B);
    for (int i = 1; i < R; i++)
      cin >> r[i];
    for (int i = 1; i < G; i++)
      cin >> g[i];
    for (int i = 1; i < B; i++)
      cin >> b[i];
    Solve();
  }
  
  return 0;
}