#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 2000005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, q, r;

bool Read() {
  cin >> n >> r;

  return 1;
}

void Process() {
  cout << "Case #" << ++ct << ":";
  if (r == n) cout << " 0";
  else {
    int dn = n - r;
    set<int> ans;
    for (int i = 1; i * i <= dn; i++)
      if (dn % i == 0) {
        ans.insert(i);
        ans.insert(dn / i);
      }
    for (int x : ans) 
      if (x > r)
        cout << " " << x;
  }
  cout << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}