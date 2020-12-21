#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;
const double H = sqrt(3.) / 2., X = 1. / sqrt(3.), R = 1. / (2. * sqrt(3.));

int ct = 0;
ll n, m;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;

  return 1;
}

double D_Same_Row(ll _n, ll _m) {
  if (_n % 2 == _m % 2)
    return abs(_m - _n) / 2;
  if (_n > m)
    _n--;
  else
    _n++;
  return X + abs(_m - _n) / 2;
}

ll Plus(ll _r, ll _s) {
  return (_s - _r) * ((_r + 1) * 2 + _s * 2) / 2;
}

double Pyt(double _c1, double _c2) {
  return sqrt(_c1 * _c1 + _c2 * _c2);
}

void Process() {
  double ans = 0;
  if (n > m) {
    double temp = n;
    n = m;
    m = temp;
  }
  ll row_n = 0, row_m = 0;
  while (1) {
    if (n >= row_n * row_n && n < (row_n + 1) * (row_n + 1))
      break;
    row_n++;
  }
  while (1) {
    if (m >= row_m * row_m && m < (row_m + 1) * (row_m + 1))
      break;
    row_m++;
  }
  if (row_n == row_m) 
    ans = D_Same_Row(n, m);
  else {
    double x, y;
    if ((row_m - row_n) % 2) {
      double multx = 1.;
      if ((row_n % 2) != (n % 2))
        multx = 2.;
      y = (double)((row_m - 1ll) - row_n) * H + X * multx;
    }
    else 
      y = (row_m - row_n) * H;
    n += Plus(row_n, row_m);
    if ((n % 2) != (m % 2)) {
      if ((row_m % 2) == (m % 2)) 
        y += R;
      else 
        y -= R;
      if (n > m)
        n--;
      else
        n++;
      x = 0.5 + D_Same_Row(n, m);
    }
    else
      x = D_Same_Row(n, m);
    ans = Pyt(x, y);
  }
  cout << fixed << setprecision(3) << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}