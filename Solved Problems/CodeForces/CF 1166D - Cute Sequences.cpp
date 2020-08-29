#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;
const ll BIG = 0x3f3f3f3f3f3f3f3f;

int ct = 0;
ll a, b, m;
ll r[55];

bool Read() {
  cin >> a;
  if (cin.eof())
    return 0;
  cin >> b >> m;

  return 1;
}

void Process() {
  if (b == a) {
    cout << "1 " << a << "\n";
    return;
  }
  if (b <= a + m) {
    cout << "2 " << a << " " << b << "\n";
    return;
  }
  ll p, sum = 0;
  for (ll i = 3; i < 50; i++) {
    p = (1ll << (i - 2));
    if (BIG / p < a)
      break;
    if (b >= p * (a + 1) && b <= p * (a + m)) {
      cout << i << " ";
      sum = p * a;
      p /= 2;
      for (int j = 2; j <= i; j++, p /= 2) {
        r[j] = (b - sum - p) / max(1ll, p);
        if (r[j] > m)
          r[j] = m;
        sum += r[j] * p;
      }
      cout << a << " ";
      sum = a;
      for (int j = 2; j <= i; j++) {
        cout << sum + r[j] << " ";
        sum += sum + r[j];
      }
      cout << "\n";
      return;
    }
  }
  cout << "-1\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}