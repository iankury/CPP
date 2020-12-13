#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

vi degree;
vector<unordered_set<int>> adj;

struct pinha_compare {
  bool operator() (int p, int q) const {
    if (degree[p] == degree[q])
      return p < q;
    return degree[p] < degree[q];
  }
};

bool Two(int k, int root) {
  vi ans{ root };
  for (int v : adj[root]) {
    for (int x : ans)
      if (!adj[v].count(x))
        return 0;
    ans.push_back(v);
  }
  cout << "2\n";
  for (int x : ans)
    cout << x << " ";
  cout << "\n";

  return 1;
}

bool One(int n, int m, int k) {
  degree.assign(n + 1, 0);
  for (int i = 1; i <= n; i++)
    degree[i] = adj[i].size();
  set<int, pinha_compare> S;
  for (int i = 1; i <= n; i++)
    S.insert(i);
  while (S.size() > 0) {
    const int u = *S.begin();
    if (degree[u] >= k) {
      cout << "1 " << S.size() << "\n";
      for (int x : S)
        cout << x << " ";
      cout << "\n";
      return 1;
    }
    else {
      if (degree[u] == k - 1 && S.size() >= k) {
        if (Two(k, u))
          return 1;
      }
      for (int v : adj[u]) {
        S.erase(v);
        adj[v].erase(u);
        degree[v] = adj[v].size();
        if (degree[v] > 0)
          S.insert(v);
      }
      S.erase(u);
    }
  }
  return 0;
}

int main() {
  io();

  int T;
  cin >> T;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;
    adj = vector<unordered_set<int>>(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].insert(v);
      adj[v].insert(u);
    }
    if (k == 1) {
      cout << "2\n1\n";
      continue;
    }
    if (One(n, m, k))
      continue;
    cout << "-1\n";
  }

  return 0;
}