#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;

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
  Mint operator * (const Mint& _a) const { return ll(x) * _a.x % M; }
  Mint operator / (const Mint& _a) const { return ll(x) * _a.MMI().x % M; }
  bool operator == (const Mint& _a) const { return x == _a.x; }
  bool operator != (const Mint& _a) const { return x != _a.x; }
  Mint& operator += (const Mint& _a) { *this = *this + _a; return *this; }
  Mint& operator -= (const Mint& _a) { *this = *this - _a; return *this; }
  Mint& operator *= (const Mint& _a) { *this = *this * _a; return *this; }
  Mint& operator /= (const Mint& _a) { *this = *this / _a; return *this; }
  istream& operator >> (istream& is) { is >> this->x; return is; }
  ostream& operator << (ostream& os) const { os << this->x; return os; }
};

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

Mint C(int _a, int _b) {
  Mint ans = 1;
  for (int i = 0; i < _b; i++) {
    ans *= _a - i;
    ans /= i + 1;
  }
  return ans;
}

int main() {
  FASTIO();

  

  return 0;
}