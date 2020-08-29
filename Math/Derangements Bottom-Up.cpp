#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int N = 1000 * 1000 + 3, M = 1000000007, BIG = 0x3f3f3f3f;

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

Mint n;

vector<Mint> derangement(N);
void Build_Derangements() {
  derangement[0] = derangement[1] = 0;
  derangement[2] = 1;
  for (int i = 3; i < N; i++)
    derangement[i] = Mint(i - 1) * (derangement[i - 1] + derangement[i - 2]);
}

Mint Process() {
  return derangement[n];
}

void Output() {
  Mint ans = Process();
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  Build_Derangements();

  while (cin >> n)
    Output();

  return 0;
}