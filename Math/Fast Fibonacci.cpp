#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

vector<ll> Fib_Aux(ll _n) {
  if (_n == 1) 
    return { 0, 1, 1, 1, };
  vector<ll> x = Fib_Aux(_n / 2);
  x = { ((x[0] * x[0]) % M + (x[1] * x[2]) % M) % M,
       ((x[0] * x[1]) % M + (x[1] * x[3]) % M) % M,
       ((x[2] * x[0]) % M + (x[3] * x[2]) % M) % M,
       ((x[2] * x[1]) % M + (x[3] * x[3]) % M) % M };
  if (_n % 2)
    x = { x[1], (x[0] + x[1]) % M, x[3], (x[2] + x[3]) % M };
  return x;
}

ll Fast_Fib(ll _n) { return Fib_Aux(_n + 1)[0]; }

ll n;

void Process() {
  cout << Fast_Fib(n) << "\n";
}

int main() {
  FASTIO();

  while (cin >> n) {
    Process();

    if (cin.eof())
      break;
  }

  return 0;
}