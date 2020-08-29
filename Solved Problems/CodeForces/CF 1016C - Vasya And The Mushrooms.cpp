#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 300005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
int a[2][N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 0; i < n; i++)
    cin >> a[0][i];
  for (int i = 0; i < n; i++)
    cin >> a[1][i];

  return 1;
}

void Process() {
  ll x, s1, s2, q1, q2, q3;
  x = a[0][n] = a[1][n] = s2 = q2 = q3 = 0;
  for (ll i = n - 1; i >= 0; i--) {
    s1 = s2 + a[0][i] + a[1][i];
    q1 = q3 + i * a[i & 1][i] + (i + 1) * a[i & 1][i + 1] +
      (-i + 2 * n - 2) * a[!(i & 1)][i + 1] + (-i + 2 * n - 1) * a[!(i & 1)][i];
    x = max(q1 + i * s1, x + (i * 2) * a[i & 1][i] +
      (i * 2 + 1) * a[!(i & 1)][i]);
    s2 = s1; q3 = q2; q2 = q1;
  }
  cout << x << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}