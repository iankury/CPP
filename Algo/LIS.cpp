#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int BIG = 0x3f3f3f3f;

vi LIS;
void Build_LIS(const vi& _v) {
  vi len(_v.size()), sorted;
  sorted.reserve(_v.size() + 1);
  sorted.push_back(-BIG);
  vi::iterator it;
  for (int i = 0; i < _v.size(); i++) {
    it = lower_bound(begin(sorted), end(sorted), _v[i]);
    len[i] = it - begin(sorted);
    if (it == end(sorted))
      sorted.push_back(_v[i]);
    else
      *it = _v[i];
  }
  int j = -BIG, cur = BIG;
  for (int i = 0; i < len.size(); i++)
    j = max(j, len[i]);
  LIS.resize(j);
  for (int i = _v.size() - 1; j; i--) 
    if (_v[i] < cur && len[i] == j) 
      LIS[--j] = _v[i];
}

int main() {
  int n;
  vi v;
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  Build_LIS(v);
  cout << "LIS length is " << LIS.size() << "\n";
  cout << "And LIS is ";
  for (int x : LIS)
    cout << x << " ";
  cout << "\n";

  return 0;
}