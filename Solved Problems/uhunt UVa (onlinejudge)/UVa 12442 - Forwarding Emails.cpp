#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 50005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N], L[N], root[N], gate;
bool vis[N];

bool Read() {
  memset(a, -1, sizeof a);
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 1; i <= n; i++) {
    int p, q;
    cin >> p >> q;
    a[p] = q;
  }

  return 1;
}

int Length(int i) {
  return root[i] == i ? L[i] : L[root[i]];
}

int Walk(int u) {
  vis[u] = 1;
  int v = a[u];
  int& ans = L[u];
  ans = 1;
  if (v == -1) root[u] = u;
  else {
    if (vis[v]) {
      if (root[v] == -1) 
        gate = v;
      else 
        ans += Length(v);
    }
    else ans += Walk(v);

    if (gate == -1) 
      root[u] = u;
    else {
      root[u] = gate;
      if (u == gate)
        gate = -1;
    }
  }
  return ans;
}

void Process() {
  memset(L, -1, sizeof L);
  memset(root, -1, sizeof root);
  memset(vis, 0, sizeof vis);
  int ans = 0, mx = 0;
  for (int i = 1; i <= n; i++) 
    if (!vis[i])
      Walk(i);
  for (int i = 1; i <= n; i++)
    if (Length(i) > mx) {
      mx = Length(i);
      ans = i;
    }
  cout << "Case " << ++ct << ": " << ans << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}