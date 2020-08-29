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

const int P = 1e6 + 55;
int FPF[P]; // First Prime Factor

void Sieve() {
  memset(FPF, 0, sizeof FPF);
  for (int i = 2; i * i < P; i++)
    if (FPF[i] == 0)
      for (int j = i * i; j < P; j += i)
        FPF[j] = i;
  for (int i = 1; i < P; i++)
    if (FPF[i] == 0)
      FPF[i] = i;
}

map<int, int> Factor(int _a) {
  map<int, int> factors;
  int d, pw;
  while (_a > 1) {
    d = FPF[_a];
    pw = 0;
    while (_a % d == 0) {
      pw++;
      _a /= d;
    }
    factors[d] = pw;
  }
  return factors;
}

int main() {
  FASTIO();

  Sieve();

  return 0;
}