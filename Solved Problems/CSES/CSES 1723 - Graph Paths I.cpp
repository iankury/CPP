#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

const int M = 1000000007;

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

int main() {
  io();

  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<Mint>> a(n, vector<Mint>(n));
  
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    a[u - 1][v - 1] += 1;
  }

  a = Matrix::Power(a, k);

  cout << a[0][n - 1] << "\n";

  return 0;
}