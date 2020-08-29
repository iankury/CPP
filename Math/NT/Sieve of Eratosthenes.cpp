#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const vi FPF = [] {
  const int P = 1e6 + 5;
  vi ans(P, 0);
  for (int i = 2; i * i < P; i++)
    for (int j = i * i; j < P; j += i)
      if (ans[j] == 0)
        ans[j] = i;
  return ans;
}();

int main() {
  ios_base::sync_with_stdio(0); 
  cin.tie(0);



  return 0;
}