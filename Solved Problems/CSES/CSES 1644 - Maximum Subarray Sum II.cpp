#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

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
};

int n, p, q;
vector<ll> a, psa;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  a.resize(n + 1);
  psa.resize(n + 1);
  cin >> p >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
	
  return 1;
}

void Process() {
	ll cur = -1e18, ans = -1e18, ssa = 0, sum, rmq;
	int lo, hi;
	psa[0] = 0;
  psa[1] = a[1];
  for (int i = 2; i <= n; i++)
    psa[i] = psa[i - 1] + a[i];
	sum = psa[n];
	SegTree<ll> tree(psa);
	for (int i = n; i >= p; i--) {
		lo = max(1, i - q);
		hi = i - p;
		cur = sum;
		cur -= ssa;
		if (lo <= hi) {
			rmq = tree.RMQ(1, lo, hi);
			if (i <= q)
				rmq = min(rmq, 0ll);
			cur -= rmq;
		}
		ssa += a[i];
		ans = max(ans, cur);
	}
	cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}