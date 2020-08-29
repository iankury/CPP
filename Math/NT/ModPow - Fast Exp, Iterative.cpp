#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int M = 1000000007;

ll ModPow(ll _a, ll _b, ll _MOD) {
  ll ans = 1;
  while (_b > 0) {
    if (_b & 1)
      ans = (ans * _a) % _MOD;
    _a = (_a * _a) % _MOD;
    _b >>= 1;
  }
  return ans;
}

int main() {
  FASTIO();

  return 0;
}