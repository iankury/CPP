#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
int a[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  int ans = 0, sum = 0, x, rem;
  for (int i = 0; i < n; i++)
    sum += a[i];
  x = sum / n;
  rem = sum % n;
  if (rem) {
    sort(a, a + n);
    for (int i = 0; i < n - rem; i++)
      ans += abs(a[i] - x);
    x++;
    for (int i = n - rem; i < n; i++)
      ans += abs(a[i] - x);
  }
  else {
    for (int i = 0; i < n; i++)
      ans += abs(a[i] - x);
  }
  cout << ans / 2 << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}