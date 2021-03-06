#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <float.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 52, M = 1005, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, subgraph_sz, rewards[N], a[N][N], dp[14][32888], decode[14];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  int p, q;
  double d;
  memset(rewards, 0, sizeof rewards);
  memset(a, BIG, sizeof a);
  for (int i = 0; i < m; i++) {
    cin >> p >> q >> d;
    a[p][q] = a[q][p] = min(a[p][q], (int)(100. * (d + 0.001)));
  }
  for (int i = 0; i <= n; i++)
    a[i][i] = 0;
  cin >> subgraph_sz;
  subgraph_sz++;
  int temp;
  decode[0] = 0;
  for (int i = 1; i < subgraph_sz; i++) {
    cin >> temp >> d;
    if (rewards[temp]) {
      i--;
      subgraph_sz--;
    }
    rewards[temp] += 100. * (d + 0.001);
    decode[i] = temp;
  }

  return 1;
}

int DP(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (!j) return a[0][decode[i]];
  int& ans = dp[i][j];
  ans = BIG;
  for (int k = 0; k < subgraph_sz; k++) 
    if (j & (1 << k))
      ans = min(ans, a[decode[i]][decode[k + 1]] + DP(k + 1, j - (1 << k)));
  return ans;
}

int Saved(int mask) {
  int ans = 0;
  for (int i = 0; i < subgraph_sz; i++)
    if (mask & (1 << i))
      ans += rewards[decode[i + 1]];
  return ans;
}

string Format_Dollars(int p) {
  string ans = "$";
  ans.append(to_string(p / 100));
  ans.push_back('.');
  if (p % 100 < 10) ans.push_back('0');
  ans.append(to_string(p % 100));
  return ans;
}

void Floyd() {
  for (int k = 0; k <= n; k++)
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= n; j++)
        a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
}

void Process() {
  memset(dp, -1, sizeof dp);
  Floyd();
  int ans = 0;
  for (int i = 0; i < (1 << (subgraph_sz - 1)); i++) 
    ans = max(ans, Saved(i) - DP(0, i));
  if (ans) cout << "Daniel can save " << Format_Dollars(ans) << "\n";
  else cout << "Don't leave the house\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}