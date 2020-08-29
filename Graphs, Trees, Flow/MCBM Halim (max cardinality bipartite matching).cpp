#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class MCBM {
  int n_vertices, n_left;
  vector<bool> vis;
  const vector<vi>& g;
  vi match;
  bool Aug(int _l) {
    if (vis[_l])
      return 0;
    vis[_l] = 1;
    for (int _r : g[_l])
      if (match[_r] == -1 || Aug(match[_r])) {
        match[_r] = _l;
        return 1;
      }
    return 0;
  }
public:
  int mcbm;
  MCBM(const vector<vi>& g, int n_left) : n_vertices(g.size()), n_left(n_left), g(g) {
    mcbm = 0;
    match.assign(n_vertices + 1, -1);
    for (int l = 1; l <= n_left; l++) {
      vis.assign(n_left + 1, 0);
      mcbm += Aug(l);
    }
  }
  vii Pairs() {
    vii ans;
    for (int i = n_left + 1; i <= n_vertices; i++)
      if (match[i] != -1)
        ans.push_back({ match[i], i - n_left });
    return ans;
  }
}; // use n_left as offset for right vertices when building graph!

int main() {

  return 0;
}