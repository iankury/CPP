#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int main() {
  io();

  const vector<ll> end = [&]() {
    vector<ll> a(18);
    ll multiplier = 1;
    for (ll i = 1; i < a.size(); i++, multiplier *= 10) 
      a[i] = a[i - 1] + 9ll * multiplier * i;
    return a;
  }();

  int T;
  cin >> T;
  while (T--) {
    ll k;
    cin >> k;

    int i = 0;
    while (end[++i] < k);

    ll initial_number = 1;
    for (int j = 1; j < i; j++)
      initial_number *= 10;

    k -= end[i - 1];

    const ll q = k / i;
    const ll rem = k % i;

    const string number = to_string(initial_number - 1 + q + bool(rem));
    const int digit = int{ number[(rem + i - 1) % i] } - 48;

    cout << digit << "\n";
  }

  return 0;
}