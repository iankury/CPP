#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
inline ll Pow(ll A, ll B, ll M) { ll Y = 1; while (B > 0) { if (B & 1)Y = Y * A % M; A = A * A % M; B >>= 1; }return Y; }

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

const int miller_rabin_precision = 30;
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
bool Prime(ll _x) {
  if (_x <= 1) return 0; if (_x <= 3) return 1; if (!(_x & 1)) return 0;
  ll d = _x - 1, a, x;
  while (d % 2 == 0)
    d /= 2;
  for (int i = 0; i < miller_rabin_precision; i++)
    if ([&]() { a = 2 + rng() % (_x - 4);
      x = Pow(a, d, _x);
      if (x == 1 || x == _x - 1)
        return 1;
      while (d != _x - 1) {
        x = (x * x) % _x;
          d *= 2;
          if (x == 1)
            return 0;
          if (x == _x - 1)
            return 1;
      } return 0; }() == 0)
      return 0;
        return 1;
}

int main() {
  FASTIO();

  return 0;
}