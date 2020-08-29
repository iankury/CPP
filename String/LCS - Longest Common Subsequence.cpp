#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;

struct Levenshtein {
  const string& a, b;
  int distance;
  int LCS;
  vector<vi> dp;
  void Bottom_Up() {
    for (int i = 0; i <= a.length(); i++)
      dp[0][i] = i;
    for (int i = 0; i <= b.length(); i++)
      dp[i][0] = i;
    for (int i = 1; i <= b.length(); i++)
      for (int j = 1; j <= a.length(); j++)
        dp[i][j] = b[i - 1] == a[j - 1] ? dp[i - 1][j - 1]
        : 1 + min(dp[i - 1][j], dp[i][j - 1]);
    distance = dp[b.length()][a.length()];
  }
  Levenshtein(const string& a, const string& b) : a(a), b(b) {
    dp.assign(b.length() + 1, vi(a.length() + 1));
    Bottom_Up();
    LCS = (a.length() + b.length() - distance) / 2;
  }
};

int main() {
  FASTIO();

  string r, s;
  cin >> r >> s;
  Levenshtein lev(r, s);
  cout << "LCS " << lev.LCS << "\n";

  return 0;
}