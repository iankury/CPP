#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;
typedef vector<int> vi;
const int N = 200009, K = 100001, M = 1000000007, BIG = 2147483647;

struct ST {
	int n;
	vi a, st;
	int freq[N], idx[N];
	int F(int x) { return freq[a[x] + K]; }
	int I(int x) { return idx[a[x] + K]; }
	ST(int _n) : n(_n) { a.resize(_n + 1); st.resize((_n + 1) * 4); memset(freq, 0, sizeof freq); }
	void Build(int p, int L, int R) {
		if (L == R) st[p] = F(L);
		else {
			int mid = L + (R - L) / 2, l = p << 1, r = l + 1;
			Build(l, L, mid);
			Build(r, mid + 1, R);
			st[p] = st[l] < st[r] ? st[r] : st[l];
		}
	}
	int Q(int p, int L, int R, int i, int j) {
		if (R < i || L > j || L > R) return -BIG;
		if (L >= i && R <= j) return st[p];
		int mid = L + (R - L) / 2, l = p << 1, r = l + 1;
		return max(Q(l, L, mid, i, j), Q(r, mid + 1, R, i, j));
	}
	void Build() {
		int last = a[1];
		freq[last + K]++;
		idx[last + K] = 1;
		for (int i = 2; i <= n; i++) {
			freq[a[i] + K]++;
			if (a[i] != last) {
				idx[a[i] + K] = i;
				last = a[i];
			}
		}
		Build(1, 1, n);
	}

	int Q(int i, int j) { return Q(1, 1, n, i, j); }
};

void Process() {
	int n, q, l, r, x, y;
	while (cin >> n, n) {
		cin >> q;
		ST* st = new ST(n);
		for (int i = 1; i <= n; i++) cin >> st->a[i];
		st->Build();
		while (q--) {
			cin >> l >> r;
			if (st->a[l] == st->a[r]) cout << r - l + 1 << "\n";
			else {
				x = st->I(l) + st->F(l);
				y = st->I(r);
				int a = st->Q(x, y - 1);
				int b = x - l;
				if (b > a) a = b;
				b = r - y + 1;
				if (b > a) a = b;
				cout << a << "\n";
			}
		}
		delete st;
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}