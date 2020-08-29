#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

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

ll numPF(ll _a) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
  while (PF * PF <= _a) {
    while (_a % PF == 0) { 
      _a /= PF; 
      ans++; 
    }
    PF = primes[++PF_idx];
  }
  if (_a != 1) 
    ans++;
  return ans;
}


int main() {
  FASTIO();

  Sieve();

  return 0;
}