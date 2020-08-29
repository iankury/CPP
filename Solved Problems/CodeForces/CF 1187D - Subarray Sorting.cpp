#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 300005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
int a[N], b[N];

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
		int l = (p << 1), r = l + 1, mid = _L + (_R - _L) / 2;
		Build(l, _L, mid);
		Build(r, mid + 1, _R);
		st[p] = min(st[l], st[r]);
	}
public:
	SegTree(const vector<T>& _a) : src_arr(_a) {
		size_t tree_sz = _a.size() << 2;
		st.resize(tree_sz);
		L.resize(tree_sz);
		R.resize(tree_sz);
		Build(1, 1, _a.size() - 1);
	}
	T RMQ(int p, int i, int j) {
		if (j < L[p] || i > R[p])
			return BIG;
		if (L[p] >= i && R[p] <= j)
			return st[p];
		return min(RMQ(p << 1, i, j), RMQ((p << 1) + 1, i, j));
	}
	void Update(int arr_idx, T value) {
		int p = 1;
		while (L[p] < R[p]) {
			p *= 2;
			if (arr_idx > R[p])
				p++;
		}
		st[p] = value;
		p /= 2;
		while (p) {
			st[p] = min(st[p << 1], st[(p << 1) + 1]);
			p /= 2;
		}
	}
};

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];

  return 1;
}

void Process() {
  vector<vi> S(n + 1);
  for (int i = n; i >= 1; i--) 
    S[a[i]].push_back(i);
	vi mins(n + 1);
	for (int i = 1; i <= n; i++)
		mins[i] = S[i].empty() ? BIG : S[i].back();
	SegTree<int> tree(mins);
  for (int i = 1; i <= n; i++) {
		if (S[b[i]].empty()) {
			cout << "NO\n";
			return;
		}
		if (tree.RMQ(1, 1, b[i] - 1) < S[b[i]].back()) {
			cout << "NO\n";
			return;
		}
		S[b[i]].pop_back();
		tree.Update(b[i], S[b[i]].empty() ? BIG : S[b[i]].back());
  }
	cout << "YES\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}