#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

ll EulerPhi(ll _a) {
  ll i, ans = _a;
  for (i = 2; i * i <= _a; i++)
    if (_a % i == 0) {
      while (_a % i == 0)
        _a /= i;
      ans -= ans / i;
    }
  if (_a > 1)
    ans -= ans / _a;
  return ans;
}

int main() {
  FASTIO();

  return 0;
}