#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, dp[82][82];
string s;

int DP(int l, int r) {
  if (l == r)
    return 1;
  else if (l + 1 == r)
    return s[l] == s[r] ? 1 : 2;
  if (dp[l][r] != BIG)
    return dp[l][r];
  int mn = BIG;
  int len = r + 1 - l;
  for (int i = 1; i <= len / 2; i++) {
    string p = s.substr(l, i);
    int x = DP(l, l + i - 1);
    int j = 1;
    for (; j < len / i; j++) {
      if (p == s.substr(l + i * j, i)) 
        mn = min(mn, x + ((j + 1) * i == len ? 0 : DP(l + (j + 1) * i, r)));
      else
        break;
    }
  }
  return dp[l][r] = min(mn, min(1 + DP(l + 1, r), 1 + DP(l, r - 1)));
}

void Process() {
  n = s.length();
  memset(dp, 0x3f, sizeof dp);
  cout << DP(0, n - 1) << "\n";
}

int main() {
  FASTIO();

  while (getline(cin, s)) {
    if (s.find_first_of('*') != string::npos)
      break;
    Process();

    if (cin.eof())
      break;
  }

  return 0;
}