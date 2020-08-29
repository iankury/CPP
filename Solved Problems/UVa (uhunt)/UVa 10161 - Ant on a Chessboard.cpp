#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

ll Time_At_Diag(ll diag) {
  return 1ll + diag * (diag - 1ll);
}

int main() {
  FASTIO();

  ll n, diag, t1, t2, x, y;
  while (cin >> n, n) {
    for (diag = 1; diag < 45055; diag++) {
      t1 = Time_At_Diag(diag);
      t2 = Time_At_Diag(diag + 1);
      if (n >= t1 && n < t2)
        break;
    }
    x = diag + t1 - n;
    y = diag;
    if (x <= 0) {
      x = abs(x) + 1;
      y++;
    }
    if (diag & 1) 
      cout << x << " " << y << "\n";
    else 
      cout << y << " " << x << "\n";
  }

  return 0;
}