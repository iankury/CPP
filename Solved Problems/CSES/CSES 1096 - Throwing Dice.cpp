#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int M = 1000000007, BIG = 0x3f3f3f3f;

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
ostream& operator << (ostream& os, const Mint& _a) { os << _a.x; return os; }

#define vvt vector<vector<T>>
namespace Matrix {
  template <typename T>
  vvt Zero(int _n, int _m) { return vvt(_n, vector<T>(_m, 0)); }
  template <typename T>
  vvt Identity(int _n) {
    vector<vector<T>> ans = Zero<T>(_n, _n);
    for (int i = 0; i < _n; i++)
      ans[i][i] = 1;
    return ans;
  }
  template <typename T>
  vvt Multiplication(const vvt& _a, const vvt& _b) {
    assert(_a[0].size() == _b.size());
    vvt ans = Zero<T>(_a.size(), _b[0].size());
    for (int i = 0; i < _a.size(); i++)
      for (int j = 0; j < _b[0].size(); j++)
        for (int k = 0; k < _a[0].size(); k++)
          ans[i][j] += _a[i][k] * _b[k][j];
    return ans;
  }
  template <typename T>
  vvt Power(vvt _a, ll expo) {
    vvt ans = Identity<T>(_a.size());
    while (expo > 0) {
      if (expo & 1)
        ans = Multiplication(ans, _a);
      expo >>= 1;
      _a = Multiplication(_a, _a);
    }
    return ans;
  }
}

ll n;

#define matrix vector<vector<Mint>>

const matrix initial = { { 32 }, { 16 }, { 8 }, { 4 }, { 2 }, { 1 } };
const matrix multiplier = {
  { 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0 }
};

Mint Process() {
  if (n <= 6)
    return initial[6 - n][0];
  const ll expo = n - 6;
  const matrix m = Matrix::Multiplication(Matrix::Power(multiplier, expo), initial);
  return m[0][0];
}

void Output() { cout << Process() << "\n"; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  while (cin >> n)
    Output();

  return 0;
}