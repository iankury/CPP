#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef vector<double> vd;

inline double Pow(double _a, int _b) {
  double ans = 1;
  while (_b > 0) {
    if (_b & 1)
      ans *= _a;
    _a *= _a;
    _b >>= 1;
  }
  return ans;
}

int main() {
  io();

  double n, k, sum;
  cin >> n >> k;

  vd p(k + 1);
  sum = p[1] = Pow(1. / k, n);

  for (int i = 2; i <= k; i++) {
    p[i] = Pow(double(i) / k, n) - sum;
    sum += p[i];
  }

  double ans = 0;

  for (int i = 1; i <= k; i++) 
    ans += double(i) * p[i];
  
  cout << fixed << setprecision(6) << ans << "\n";

  return 0;
}