#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int a[N], n;

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

void Process() {
	
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}