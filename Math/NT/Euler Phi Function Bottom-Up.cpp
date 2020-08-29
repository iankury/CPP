#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

const int P = 1000000;
ll EulerPhi[P];
void Build_Euler_Phi() {
  for (int i = 1; i <= P; i++) 
    EulerPhi[i] = i;
  for (int i = 2; i <= P; i++)
    if (EulerPhi[i] == i)
      for (int j = i; j <= P; j += i)
        EulerPhi[j] = (EulerPhi[j] / i) * (i - 1);
}

int main() {
  FASTIO();

  return 0;
}