#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 60005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int sum[N];

int main() {
  FASTIO();

  memset(sum, 0, sizeof sum);
  for (int i = 1; i < 30001; i++) 
    for (int j = i + i; j < 60001; j += i) 
      sum[j] += i;
  cout << "PERFECTION OUTPUT\n";
  int u;
  while (cin >> u) {
    if (u == 0)
      break;
    cout << right << setw(5) << u << "  ";
    if (u == sum[u])
      cout << "PERFECT\n";
    else if (u > sum[u])
      cout << "DEFICIENT\n";
    else
      cout << "ABUNDANT\n";
  }
  cout << "END OF OUTPUT\n";

  return 0;
}