#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

ll n;
string s;
ll fac[21];
void Build_Fac() {
  fac[0] = fac[1] = 1;
  for (int i = 2; i < 21; i++)
    fac[i] = fac[i - 1] * i;
}

bool Read() {
  cin >> s >> n;

  return 1;
}

void Solve(string p) {
  char ans;
  ll l = p.length();
  ll q = n / fac[l - 1];
  n %= fac[l - 1];
  ans = p[q];
  cout << ans;
  p.erase(q, 1);
  if (!p.empty())
    Solve(p);
}

void Process() {
  sort(begin(s), end(s));
  Solve(s);
  cout << "\n";
}

int main() {
  FASTIO();

  Build_Fac();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}