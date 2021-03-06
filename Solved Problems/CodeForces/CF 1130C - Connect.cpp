#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 53, M = 1000000007;
int n, sz_st = 0, sz_en = 0;
char a[N][N];
bool cur;

struct Point {
	int r, c;
	int Dist(const Point& p) {
		int dr = r < p.r ? p.r - r : r - p.r;
		int dc = c < p.c ? p.c - c : c - p.c;
		return dr * dr + dc * dc;
	}
	bool operator == (const Point& p) const { return r == p.r && c == p.c; }
};
Point st, en;
Point shore_st[2511], shore_en[2511];

bool In_Bounds(const Point& p) { return p.r && p.r <= n && p.c && p.c <= n; }

bool filled[N][N];

bool Fill(const Point& p) {
	if (!In_Bounds(p) || a[p.r][p.c] == '1') return 0;
	filled[p.r][p.c] = 1;
	if (p.c == en.c && p.r == en.r) return 1;
	bool ans = 0;
	if (!filled[p.r + 1][p.c]) ans = (ans || Fill({ p.r + 1 , p.c }));
	if (!filled[p.r - 1][p.c]) ans = (ans || Fill({ p.r - 1 , p.c }));
	if (!filled[p.r][p.c + 1]) ans = (ans || Fill({ p.r , p.c + 1 }));
	if (!filled[p.r][p.c - 1]) ans = (ans || Fill({ p.r , p.c - 1 }));
	return ans;
}

void Shore(const Point& p) {
	if (!In_Bounds(p) || a[p.r][p.c] == '1') return;
	filled[p.r][p.c] = 1;
	if ((p.c > 1 && a[p.r][p.c - 1] == '1') ||
		(p.c < n && a[p.r][p.c + 1] == '1') ||
		(p.r > 1 && a[p.r - 1][p.c] == '1') ||
		(p.r < n && a[p.r + 1][p.c] == '1')) {
		if (cur) {
			shore_en[sz_en] = p;
			sz_en++;
		}
		else {
			shore_st[sz_st] = p;
			sz_st++;
		}
	}
	if (!filled[p.r + 1][p.c]) Shore({ p.r + 1 , p.c });
	if (!filled[p.r - 1][p.c]) Shore({ p.r - 1 , p.c });
	if (!filled[p.r][p.c + 1]) Shore({ p.r , p.c + 1 });
	if (!filled[p.r][p.c - 1]) Shore({ p.r , p.c - 1 });
	return;
}

void Clear_Filled() { for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) filled[i][j] = 0; }

void Process() {
	Clear_Filled();
	cin >> n >> st.r >> st.c >> en.r >> en.c;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
	if (Fill(st)) cout << "0\n";
	else {
		int ans = 2123456789;
		Clear_Filled();
		cur = 0;
		Shore(st);
		Clear_Filled();
		cur = 1;
		Shore(en);
		for (int i = 0; i < sz_st; i++) {
			for (int j = 0; j < sz_en; j++) {
				int d = shore_st[i].Dist(shore_en[j]);
				if (d < ans) ans = d;
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