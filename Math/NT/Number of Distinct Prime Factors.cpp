#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int P = 1000005;
ll numDiffPF[P];

void Build_Num_Diff_Prime_Factors() {
  memset(numDiffPF, 0, sizeof numDiffPF);
  for (int i = 2; i < P; i++)
    if (numDiffPF[i] == 0)
      for (int j = i; j < P; j += i)
        numDiffPF[j]++;
}

int main() {
  FASTIO();

  Build_Num_Diff_Prime_Factors();

  return 0;
}