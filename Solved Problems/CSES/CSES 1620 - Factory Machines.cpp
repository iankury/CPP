#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
ll n, t;
int a[N];

bool Valid(ll toym) {
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    sum += toym / a[i];
    if (sum >= t)
      return 1;
  }
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> t;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  ll p = 1, q = 0x3f3f3f3f3f3f3f3f, mid;
  while (p <= q) {
    mid = p + (q - p) / 2;
    if (!Valid(mid))
      p = mid + 1;
    else if (p < q)
      q = mid;
    else
      break;
  }
  cout << mid << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}