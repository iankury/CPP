#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;

  return 1;
}

void Process() {
  int p = 1, q = m;
  while (p < q) {
    if (p & 1) {
      for (int i = 1; i <= n; i++)
        cout << i << " " << p << "\n" << n + 1 - i << " " << q << "\n";
    }
    else {
      for (int i = 1; i <= n; i++)
        cout << n + 1 - i << " " << p << "\n" << i << " " << q << "\n";
    }
    p++;
    q--;
  }
  if (p == q) {
    int d = n - 1;
    int r = 1;
    if (p & 1 == 0) 
      d *= -1;
    while (n--) {
      cout << r << " " << p << "\n";
      r += d;
      d = d < 0 ? (d + 1) * -1 : (d - 1) * -1;
    }
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}