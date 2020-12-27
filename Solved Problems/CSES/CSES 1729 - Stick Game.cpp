#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int n, k;
vector<char> dp;
vi p;

int main() {
  io();

  cin >> n >> k;
  p.resize(k);
  dp.assign(n + 1, 0);
  for (int i = 0; i < k; i++)
    cin >> p[i];
  sort(begin(p), end(p));

  for (int i = 0; i < k; i++)
    dp[p[i]] = 'W';

  for (int i = 2; i <= n; i++) 
    if (!dp[i]) {
      dp[i] = 'L';
      for (int j = 0; j < k && i - p[j] > 0; j++) 
        if (dp[i - p[j]] == 'L')
          dp[i] = 'W';
    }

  for (int i = 1; i <= n; i++)
    cout << dp[i];
  cout << "\n";

  return 0;
}