#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<ll>> C;
void Build_C(int mx_sz, int _mod) {
  C.assign(mx_sz + 1, vector<ll>(mx_sz + 1));
  C[0][0] = 1;
  for (int i = 1; i <= mx_sz; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= mx_sz; j++) 
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % _mod;
  }
}

int main() {


  return 0;
}