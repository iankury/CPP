#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

const int N = 200000;
const ll M = 998244353;

const vector<ll> a = []() {
  vector<ll> ans{ 0, 10, 180 };
  const ll basic = 90;
  ll outer_multiplier = 10;
  ll inner_multiplier = 9;
  for (int i = 3; i <= N; i++) {
    ans.push_back(basic * 2ll * outer_multiplier % M);
    ans[i] += basic * ll(i - 2) * inner_multiplier % M;
    ans[i] %= M;
    outer_multiplier *= 10;
    outer_multiplier %= M;
    inner_multiplier *= 10;
    inner_multiplier %= M;
  }
  return ans;
}();

void Solve(int n) {
  for (int i = n; i >= 1; i--)
    cout << a[i] << " ";
  cout << "\n";
}

int main() {
  io();

  int n;
  while (cin >> n)
    Solve(n);

  return 0;
}