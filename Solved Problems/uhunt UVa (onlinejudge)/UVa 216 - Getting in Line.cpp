#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 9, M = 555, BIG = 0x3f3f3f3f;

int ct = 0;
int n, mask, pi[N][M];
double dp[N][M];

struct Point {
  int x, y;
  string Print() {
    string ans = "(";
    ans.append(to_string(x));
    ans.push_back(',');
    ans.append(to_string(y));
    ans.push_back(')');
    return ans;
  }
};
Point comp[N];

double D(const Point& p, const Point& q, bool discount) {
  if (discount && q.x == comp[0].x && q.y == comp[0].y) return 0;
  if (p.x == q.x) return 16. + abs(p.y - q.y);
  if (p.y == q.y) return 16. + abs(p.x - q.x);
  return 16. + sqrt((double)((p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x)));
}

double DP(int i, int j) {
  if (dp[i][j] > -1) return dp[i][j];
  double& ans = dp[i][j];
  if (!j) {
    ans = D(comp[0], comp[i], 1);
    pi[i][j] = 0;
  }
  else {
    ans = BIG;
    double d;
    for (int k = 0; k < N; k++) {
      if (j & (1 << k)) {
        d = D(comp[k], comp[i], 1) + DP(k, j - (1 << k));
        if (d < ans) {
          ans = d;
          pi[i][j] = k;
        }
      }
    }
  }
  return ans;
}

bool Read() {
  cin >> n;
  if (!n) return 0;
  for (int i = 0; i < n; i++) cin >> comp[i].x >> comp[i].y;

  return 1;
}

vi adj[N];

void Build_Path(int i, int j, int jump) {
  if (j >= 0 && pi[i][j] != -1) {
    Build_Path(pi[i][j], j - (1 << pi[i][j]), jump);
    if (i) adj[pi[i][j]].push_back(i);
  }
}

void Print_Recursive(int i) {
  int idx = i ? 0 : 1;
  if (!adj[i].empty()) {
    Print_Recursive(adj[i][idx]);
    cout << "Cable requirement to connect " <<
      comp[adj[i][idx]].Print() << " to " << comp[i].Print() <<
      " is " << fixed << setprecision(2) << 
      D(comp[adj[i][idx]], comp[i], 0) << " feet.\n";
  }
}

void Print_Path() {
  int cur = 0;
  if (adj[0].size() > 1) 
    Print_Recursive(0);
  cur = 0;
  while (!adj[cur].empty()) {
    cout << "Cable requirement to connect " <<
      comp[cur].Print() << " to " << comp[adj[cur][0]].Print() <<
      " is " << fixed << setprecision(2) << 
      D(comp[cur], comp[adj[cur][0]], 0) << " feet.\n";
    cur = adj[cur][0];
  }
}

void Process() {
  for (int i = 0; i < n; i++) adj[i].clear();
  memset(pi, -1, sizeof pi);
  cout << string(58, '*') << "\nNetwork #" << ++ct << "\n";
  mask = 1;
  memset(dp, -11, sizeof dp);
  double ans = DP(0, (1 << n) - 1);
  Build_Path(0, (1 << n) - 1, 0);
  Print_Path();
  cout << "Number of feet of cable required is " <<
    fixed << setprecision(2) << ans << ".\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}