#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;
typedef vector<int> vi;

const int N = 100005, M = 1000000007, BIG = 2147483647;

vi a;

#define L1(i) (i & -i)
class Fenwick_Tree {
	vi ft;
public:
	Fenwick_Tree(int _n) { ft.assign(_n + 1, 0); }
	int Q(int x) { int ans = 0; for (; x > 0; x -= L1(x)) ans += ft[x]; return ans; }
	int Q(int p, int q) { return Q(q) - Q(p - 1); }
	void Adjust(int x, int delta) { for (; x < ft.size(); x += L1(x)) ft[x] += delta; }
};

void Process() {
	while (!cin.eof()) {
		string ans = "";
		int n, k, p, q;
		char c;
		if (!(cin >> n >> k)) break;
		a.resize(n + 1);
		Fenwick_Tree z(n), neg(n);
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] < 0) neg.Adjust(i, 1);
			else if (!a[i]) z.Adjust(i, 1);
		}
		for (int i = 0; i < k; i++) {
			cin >> c >> p >> q;
			if (c == 'C') {
				if (a[p] < 0) {
					if (!q) {
						z.Adjust(p, 1);
						neg.Adjust(p, -1);
					}
					else if (q > 0) neg.Adjust(p, -1);
				}
				else if (a[p]) {
					if (!q) z.Adjust(p, 1);
					else if (q < 0) neg.Adjust(p, 1);
				}
				else {
					if (q > 0) z.Adjust(p, -1);
					else if (q < 0) {
						z.Adjust(p, -1);
						neg.Adjust(p, 1);
					}
				}
				a[p] = q;
			}
			else {
				int zeros = z.Q(p, q), negs = neg.Q(p, q);
				if (zeros) ans.push_back('0');
				else if (negs % 2) ans.push_back('-');
				else ans.push_back('+');
			}
		}
		cout << ans << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}