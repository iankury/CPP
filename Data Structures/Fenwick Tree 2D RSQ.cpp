#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int M = 1000000007, BIG = 0x3f3f3f3f;

class Fenwick2D {
	vector<vi> tree;
	const int src_n, src_m;
	int RSQ_Aux(int x, int y) {
		int s = 0;
		while (x > 0) {
			int _y = y;
			while (_y > 0) {
				s += tree[x][_y];
				_y -= _y & -_y;
			}
			x -= x & -x;
		}
		return s;
	}
public:
	void Update(int x, int y, int delta) {
		while (x <= src_n) {
			int _y = y;
			while (_y <= src_m) {
				tree[x][_y] += delta;
				_y += _y & -_y;
			}
			x += x & -x;
		}
	}
	Fenwick2D(const vector<vector<bool>>& src_arr) 
		: src_n(src_arr.size()), src_m(src_arr[0].size()) {
		tree.assign(src_n, vi(src_m, 0));
		for (int i = 1; i < src_n; i++)
			for (int j = 1; j < src_m; j++)
				if (src_arr[i][j])
					Update(i, j, 1);
	}
	int RSQ(int UL_i, int UL_j, int DR_i, int DR_j) {
		return (
			RSQ_Aux(DR_i, DR_j) -
			RSQ_Aux(DR_i, UL_j - 1) -
			RSQ_Aux(UL_i - 1, DR_j) +
			RSQ_Aux(UL_i - 1, UL_j - 1)
		);
	}
};

int n, q;
vector<vector<bool>> a;

vi Process() {
	vi ans;
	Fenwick2D tree(a);
	int t, x, y, UL_i, UL_j, DR_i, DR_j;
	for (int i = 1; i <= q; i++) {
		cin >> t;
		if (t == 1) {
			cin >> x >> y;
			a[x][y] = !a[x][y];
			tree.Update(x, y, a[x][y] ? 1 : -1);
		}
		else {
			cin >> UL_i >> UL_j >> DR_i >> DR_j;
			ans.push_back(tree.RSQ(UL_i, UL_j, DR_i, DR_j));
		}
	}

	return ans;
}

void Output() {
	const vi ans = Process();
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> n) {
		cin >> q;
		a.assign(n + 1, vector<bool>(n + 1));
		char c;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				cin >> c;
				a[i][j] = (c == '*');
			}

		Output();
	}

	return 0;
}