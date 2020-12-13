#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

struct Node {
  int id, l, r;
};

int n, k;
vector<Node> nodes;

struct pinha_compare {
  bool operator() (int p, int q) const {
    if (nodes[p].r == nodes[q].r)
      return nodes[p].id < nodes[q].id;
    return nodes[p].r < nodes[q].r;
  }
};

void Solve() {
  vi ans;
  map<int, vi> starting_at;
  for (const auto& node : nodes)
    starting_at[node.l].push_back(node.id);
  set<int, pinha_compare> S;
  for (const auto& x : starting_at) {
    const int cur_time = x.first;
    while (!S.empty()) {
      auto it = S.begin();
      const int earliest_end = nodes[*it].r;
      if (earliest_end >= cur_time)
        break;
      S.erase(it);
    }
    for (int i : x.second) 
      S.insert(i);
    while (int(S.size()) > k) {
      auto it = S.rbegin();
      const int to_kill = nodes[*it].id;
      ans.push_back(to_kill);
      S.erase(to_kill);
    }
  }
  cout << ans.size() << "\n";
  for (int x : ans)
    cout << x + 1 << " ";
  cout << "\n";
}

int main() {
  io();

  while (cin >> n) {
    cin >> k;
    nodes.resize(n);
    for (int i = 0; i < n; i++) {
      nodes[i].id = i;
      cin >> nodes[i].l >> nodes[i].r;
    }
    Solve();
  }

  return 0;
}