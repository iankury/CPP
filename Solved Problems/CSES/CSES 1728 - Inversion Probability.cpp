#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef vector<int> vi;

int main() {
  io();

  int n;
  cin >> n;
  vi a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  double ans = 0;

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      for (int k = 1; k < a[i] && k <= a[j]; k++)
        ans += ((double(a[i]) - k) / double(a[i])) * (1. / a[j]);

  cout << fixed << setprecision(6) << ans << "\n";

  return 0;
}