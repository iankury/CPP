#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
class String_Hashing {
  const int n;
  vector<ll> h, p;
  const ll A, B;
  ll Big() { return rng() % 165784923 + 842564003; }
public: 
  String_Hashing(const string& s) :
    n(s.length()),
    h(vector<ll>(n + 1)),
    p(vector<ll>(n + 1)),
    A(Big()),
    B(Big()) {
    h[0] = s[0]; p[0] = 1;
    for (int i = 1; i <= n; i++) {
      h[i] = (h[i - 1] * A + s[i]) % B;
      p[i] = p[i - 1] * A % B;
    }
  }
  ll Substring_Hash(int start_idx, int substr_length) {
    ll minus = 0;
    if (start_idx)
      minus = h[start_idx - 1] * p[substr_length];
    ll ans = (h[start_idx + substr_length - 1] - minus) % B;
    if (ans < 0)
      ans += B;
    return ans;
  }
};

int main() {
  io();

  string s;
  cin >> s;
  int n = s.length();
  String_Hashing h(s);
  for (int i = 1; i < n; i++) {
    ll prefix_hash = h.Substring_Hash(0, i);
    ll suffix_hash = h.Substring_Hash(n - i, i);
    if (prefix_hash == suffix_hash)
      cout << i << " ";
  }
  cout << "\n";

  return 0;
}