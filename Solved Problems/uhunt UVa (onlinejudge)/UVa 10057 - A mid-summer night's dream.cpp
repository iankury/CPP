#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1000005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++) cin >> a[i];

  return 1;
}

void Process() {
  sort(a, a + n);
  int m, b = 0, c = 1;
  if (!(n % 2)) {
    m = a[(n / 2) - 1];
    int m2 = m2 = a[n / 2];
    if (m != m2) {
      b = distance(lower_bound(a, a + n, m2), upper_bound(a, a + n, m2));
      c += (m2 - m);
    }
  }
  else m = a[n / 2];
  b += distance(lower_bound(a, a + n, m), upper_bound(a, a + n, m));
  cout << m << " " << b << " " << c << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}