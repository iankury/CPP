#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 11, M = 10005, BIG = 0x3f3f3f3f;
  
int ct = 0;
int l, u, n, a[N], pi[M];
bool vis[M];

void Add(int& v, int button) {
  v = (v + a[button]) % 10000;
}

int Path_Length(int p) {
  int ans = 0;
  while (pi[p] != -1) {
    p = pi[p];
    ans++;
  }
  return ans;
}

bool Read() {
  string r, s, t;
  cin >> r >> s >> t;
  l = stoi(r);
  u = stoi(s);
  n = stoi(t);
  if (!l && !u && !n) return 0;
  for (int i = 0; i < n; i++) {
    cin >> s;
    a[i] = stoi(s);
  }

  return 1;
}

void Process() {
  cout << "Case " << ++ct << ": ";
  memset(vis, 0, sizeof vis);
  pi[l] = -1;
  queue<int> Q;
  Q.push(l);
  vis[l] = 1;
  int cur;
  while (!Q.empty()) {
    cur = Q.front();
    Q.pop();
    if (cur == u) {
      cout << Path_Length(cur) << "\n";
      return;
    }
    for (int i = 0; i < n; i++) {
      int x = cur;
      Add(x, i);
      if (!vis[x]) {
        vis[x] = 1;
        Q.push(x);
        pi[x] = cur;
      }
    }
  }
  cout << "Permanently Locked\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}