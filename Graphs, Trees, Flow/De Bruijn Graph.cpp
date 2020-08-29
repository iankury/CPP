#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class Hierholzer {
  const vector<vi>& g;
  int m;
  list<int> tour;
  vector<vector<bool>> visited_edge;
  void Euler_Tour(list<int>::iterator it, int u) {
    int v;
    for (int i = 0; i < g[u].size(); i++)
      if (!visited_edge[u][i]) {
        v = g[u][i];
        visited_edge[u][i] = 1;
        Euler_Tour(tour.insert(it, u), v);
      }
  }
public:
  Hierholzer(const vector<vi>& g, int n_of_edges) : g(g), m(n_of_edges) {}
  vi Euler_Tour(int source) {
    tour.clear();
    visited_edge.assign(g.size(), vector<bool>());
    for (int i = 0; i < g.size(); i++)
      visited_edge[i].assign(g[i].size(), 0);
    Euler_Tour(begin(tour), source);
    return vi(begin(tour), end(tour));
  }
};

class DeBruijnGraph {
  int seq_len;
  vector<vi> g;
public:
  DeBruijnGraph(int seq_len) : seq_len(seq_len) {
    g.resize(1 << (seq_len - 1));
    for (int i = 0; i < g.size(); i++) {
      g[i].push_back((i << 1) % g.size());
      g[i].push_back(((i << 1) + 1) % g.size());
    }
  }
  string De_Bruijn_Sequence() {
    string ans = "0";
    Hierholzer hierholzer(g, g.size() * 2);
    for (int x : hierholzer.Euler_Tour(0))
      ans.push_back((x & 1) ? '1' : '0');
    ans.append(string(seq_len - 2, '0'));
    return ans;
  }
};

int main() {

  return 0;
}