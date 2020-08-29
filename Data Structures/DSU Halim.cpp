#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

class DSU { 
  vi root, rank, cardi;
  int Root(int i) { 
    return root[i] == i ? i : root[i] = Root(root[i]); 
  }
public:
  DSU(int _sz) {
    rank.assign(_sz + 1, 0);
    root.resize(_sz + 1);
    cardi.assign(_sz + 1, 1);
    for (int i = 0; i <= _sz; i++)
      root[i] = i;
  }
  int Cardinality(int i) {
    return cardi[Root(i)];
  }
  bool Same(int i, int j) { 
    return Root(i) == Root(j); 
  }
  void Unite(int i, int j) {
    if (Same(i, j))
      return;
    int x = Root(i), y = Root(j);
    if (rank[x] > rank[y]) {
      root[y] = x;
      cardi[x] += cardi[y];
    }
    else {
      root[x] = y;
      cardi[y] += cardi[x];
      if (rank[x] == rank[y]) 
        rank[y]++;
    }
  }
};

int main() {
  FASTIO();

  

  return 0;
}