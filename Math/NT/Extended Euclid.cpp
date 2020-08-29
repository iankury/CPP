#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

void Extended_Euclid(ll _a, ll _b, ll& g, ll& x, ll& y) {
  x = 0; y = 1;
  ll xx = 1, yy = 0, q, temp;
  while (_a) {
    q = _b / _a;
    temp = _a;
    _a = _b % _a;
    _b = temp;
    temp = y;
    y = yy;
    yy = temp - q * yy;
    temp = x;
    x = xx;
    xx = temp - q * xx;
  }
  g = _b;
}

//struct EE { ll g, x, y; };
//EE Extended_Euclid(ll _a, ll _b) {
//  if (_a == 0)
//    return { _b, 0, 1 };
//  EE rec = Extended_Euclid(_b % _a, _a);
//  return { rec.g, rec.y - (_b / _a) * rec.x, rec.x };
//}

int main() {
  FASTIO();

  return 0;
}