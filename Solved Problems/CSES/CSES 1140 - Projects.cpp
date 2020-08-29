#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Node {
  int l, r, p;
  bool operator < (const Node& _a) const {
    if (r == _a.r)
      return l > _a.l;
    return r < _a.r;
  }
};

int n;
vector<Node> a;
ll dp[N], mx[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  a.resize(n);
  for (int i = 0; i < n; i++)
    cin >> a[i].l >> a[i].r >> a[i].p;

  return 1;
}

void Process() {
  sort(begin(a), end(a));
  memset(mx, 0, sizeof mx);
  dp[0] = mx[0] = a[0].p;
  ll t;
  for (int i = 1; i < n; i++) {
    vector<Node>::iterator it = upper_bound(begin(a), end(a), Node{ -1, a[i].l - 1, 0 });
    t = it == begin(a) ? 0 : mx[prev(it) - begin(a)];
    dp[i] = t + a[i].p;
    mx[i] = max(mx[i - 1], dp[i]);
  }
  cout << mx[n - 1] << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}