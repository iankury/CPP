#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

const int P = 1000005;
bitset<P> prime;
vi primes;

void Sieve() {
  primes.reserve(80123);
  prime.set();
  prime[0] = prime[1] = 0;
  for (ll i = 2; i < P; i++)
    if (prime[i]) {
      for (ll j = i * i; j < P; j += i)
        prime[j] = 0;
      primes.push_back(i);
    }
}

ll numDiv(ll _a) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;
  while (PF * PF <= _a) {
    ll power = 0; 
    while (_a % PF == 0) { 
      _a /= PF; 
      power++; 
    }
    ans *= (power + 1);
    PF = primes[++PF_idx];
  }
  if (_a != 1) 
    ans *= 2;
  return ans;
}

bool Read() {
  cin >> n;


  return 1;
}

void Process() {

}

int main() {
  FASTIO();

  Sieve();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}