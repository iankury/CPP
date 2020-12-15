#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;
typedef list<int>::iterator iter;

struct Node {
  int id, val;
};

int n, k;
vector<Node> a;

void Solve() {
  vi sorted(n), ans(n);
  iota(begin(sorted), end(sorted), 0);
  sort(begin(sorted), end(sorted), [&](int p, int q) {
    return a[p].val < a[q].val;
  });

  vector<iter> iters(n);
  list<int> li;
  for (const auto& node : a)
    li.push_back(node.id);
  iter it = li.begin();
  for (int i = 0; i < n; i++, it++) 
    iters[i] = it;

  int turn = 1; 
  while (!sorted.empty()) {
    iter x = iters[sorted.back()];

    iter l = x, r = x;
    for (int i = 0; i < k && l != li.begin(); i++, l--);
    for (int i = 0; i <= k && r != li.end(); i++, r++);

    for (it = l; it != r; it++) 
      ans[*it] = turn;
    li.erase(l, r);

    turn = turn == 1 ? 2 : 1;
    while (!sorted.empty() && ans[sorted.back()])
      sorted.pop_back();
  }
  it = iters[sorted.back()];

  for (int x : ans)
    cout << x;
  cout << "\n";
}

int main() {
  io();

  while (cin >> n) {
    cin >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i].val;
      a[i].id = i;
    }
    Solve();
  }

  return 0;
}