#include <bits/stdc++.h>
using namespace std;

const int N = 1000 * 1000 + 5, M = 1000 * 1000 * 1000 + 7;

typedef long long ll;
typedef vector<int> vi;

struct Mint {
  int x;
  Mint(int _value = 0) : x(_value) {}
  Mint MMI() const {
    int ax = x, bx = M, sx = 1, tx = 0, qx;
    while (bx) {
      qx = ax / bx;
      ax -= qx * bx;
      sx -= qx * tx;
      swap(ax, bx);
      swap(sx, tx);
    }
    return sx >= 0 ? sx : sx + M;
  }
  operator int() { return x; }
  Mint operator - (const Mint& _a) const { int ans = x - _a.x; return ans < 0 ? M + ans : ans; }
  Mint operator + (const Mint& _a) const { int ans = x + _a.x; return ans - (ans >= M) * M; }
  Mint operator * (const Mint& _a) const { return (ll)x * _a.x % M; }
  Mint operator / (const Mint& _a) const { return (ll)x * _a.MMI().x % M; }
  bool operator == (const Mint& _a) const { return x == _a.x; }
  bool operator != (const Mint& _a) const { return x != _a.x; }
};
Mint& operator += (Mint& _a, const Mint& _b) { return _a = _a + _b; }
Mint& operator -= (Mint& _a, const Mint& _b) { return _a = _a - _b; }
Mint& operator *= (Mint& _a, const Mint& _b) { return _a = _a * _b; }
Mint& operator /= (Mint& _a, const Mint& _b) { return _a = _a / _b; }
istream& operator >> (istream& is, Mint& _a) { is >> _a.x; return is; }
ostream& operator << (ostream& os, Mint& _a) { os << _a.x; return os; }

Mint ModPow(Mint _a, ll _b) {
  Mint ans = 1;
  while (_b > 0) {
    if (_b & 1)
      ans *= _a;
    _a *= _a;
    _b >>= 1;
  }
  return ans;
}

vector<Mint> factorial(N);

void Build_Factorials() {
  factorial[0] = factorial[1] = 1;
  for (int i = 2; i < N; i++)
    factorial[i] = factorial[i - 1] * Mint(i);
}

Mint C(int _a, int _b) {
  return factorial[_a] / (factorial[_b] * factorial[_a - _b]);
}

int main() {
  Build_Factorials();

  return 0;
}