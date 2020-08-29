#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

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

  return 0;
}