#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct EE { ll x, y, d; };
struct CRT_Cong { ll rem, mod; };
ll GCD(ll a, ll b) { return (b == 0) ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }
inline ll Normalize(ll x, ll mod) { x %= mod; if (x < 0) x += mod; return x; }
EE Extended_Euclid(ll a, ll b) {
  if (b == 0)
    return { 1, 0, a };
  EE ee = Extended_Euclid(b, a % b);
  return { ee.y, ee.x - a / b * ee.y, ee.d };
}
class CRT {
  vector<CRT_Cong> cong;
public:
  CRT_Cong ans;
  bool possible;
  CRT(const vector<CRT_Cong>& _cong) : cong(_cong), possible(1) {
    for (CRT_Cong& c : cong)
      c.rem = Normalize(c.rem, c.mod);
    ans.rem = cong[0].rem;
    ans.mod = cong[0].mod;
    for (int i = 1; i < cong.size(); i++) {
      EE ee = Extended_Euclid(ans.mod, cong[i].mod);
      int x1 = ee.x;
      int d = ee.d;
      if ((cong[i].rem - ans.rem) % d != 0) {
        possible = 0;
        return;
      }
      ans.rem = Normalize(ans.rem + x1 * (cong[i].rem - ans.rem) / d
        % (cong[i].mod / d) * ans.mod, ans.mod * cong[i].mod / d);
      ans.mod = LCM(ans.mod, cong[i].mod);
    }
  }
};

int main() {
  vector<CRT_Cong> v = { {2, 3}, {3, 5}, {2, 7} };
  CRT crt(v);
  if (crt.possible)
    cout << crt.ans.rem << " mod " << crt.ans.mod << "\n";
  else
    cout << "Impossible.\n";

  return 0;
}