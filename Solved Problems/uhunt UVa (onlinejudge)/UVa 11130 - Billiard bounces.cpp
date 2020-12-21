#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;
const double PI = 3.141592653589793;

int ct = 0;
double a, b, v, A, s;

bool Read() {
  cin >> a;
  if (cin.eof())
    return 0;
  cin >> b >> v >> A >> s;
  if (a == 0 && b == 0 && v == 0 && A == 0 && s == 0)
    return 0;
 

  return 1;
}

void Process() {
  A = A * PI / 180.;
  double acc = v / s;
  double x = v * s - acc * s * s / 2;
  double w = x * cos(A);
  double h = x * sin(A);
  double rem = h - (((ll)h / (ll)b) * (ll)b);
  ll vb = (ll)h / (ll)b + (ll)(rem / (b / 2));
  rem = w - (((ll)w / (ll)a) * (ll)a);
  ll hb = (ll)w / (ll)a + (ll)(rem / (a / 2));
  cout << hb << " " << vb << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}