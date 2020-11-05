#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

template <typename T>
class SegTree {
  vi L, R;
  vector<T> st;
  const vector<T>& src_arr;
  void Build(int p, int _L, int _R) {
    L[p] = _L;
    R[p] = _R;
    if (_L == _R) {
      st[p] = src_arr[_L];
      return;
    }
    const int l = (p << 1), r = l + 1, mid = _L + (_R - _L) / 2;
    Build(l, _L, mid);
    Build(r, mid + 1, _R);
    st[p] = st[l] + st[r];
  }
public:
  SegTree(const vector<T>& _a) : src_arr(_a) {
    size_t tree_sz = _a.size() << 2;
    st.resize(tree_sz);
    L.resize(tree_sz);
    R.resize(tree_sz);
    Build(1, 1, _a.size() - 1);
  }
  T RSQ(int p, int i, int j) {
    if (j < L[p] || i > R[p])
      return 0;
    if (L[p] >= i && R[p] <= j)
      return st[p];
    return RSQ(p << 1, i, j) + RSQ((p << 1) + 1, i, j);
  }
  void Update(int arr_idx, T value) {
    int p = 1;
    while (L[p] < R[p]) {
      p <<= 1;
      if (arr_idx > R[p])
        p++;
    }
    st[p] = value;
    p >>= 1;
    while (p) {
      st[p] = st[p << 1] + st[(p << 1) + 1];
      p >>= 1;
    }
  }
};

struct Node {
  int value, dfs_in, dfs_out;
  vi adj;
};

Node nodes[200001];
vector<ll> a = { 0 };

void DFS(int u, int p) {
  nodes[u].dfs_in = a.size();
  a.push_back(nodes[u].value);
  for (int v : nodes[u].adj) {
    if (v == p)
      continue;
    DFS(v, u);
  }
  nodes[u].dfs_out = a.size();
  a.push_back(nodes[u].value);
}

int main() {
  io();

  int n, q;
  cin >> n >> q;
  
  for (int i = 1; i <= n; i++)
    cin >> nodes[i].value;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    nodes[u].adj.push_back(v);
    nodes[v].adj.push_back(u);
  }

  DFS(1, -1);

  SegTree<ll> tree(a);

  for (int i = 0; i < q; i++) {
    int type, u;
    cin >> type >> u;
    const int ix = nodes[u].dfs_in;
    const int jx = nodes[u].dfs_out;
    if (type == 1) {
      ll x;
      cin >> x;
      tree.Update(ix, x);
      tree.Update(jx, x);
    }
    else 
      cout << tree.RSQ(1, ix, jx) / 2 << "\n";
  }

  return 0;
}