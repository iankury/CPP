#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1022, N2 = 10005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, q, l[N2], u[N2];
vector<vi> h;

bool Read() {
	cin >> n >> m;
	if (!m || cin.eof()) return 0;
	int temp;
	h.clear();
	h.resize(n + m - 1);
	for (int i = n - 1; i >= 0; i--) 
		for (int j = 0; j < m; j++) {
			cin >> temp;
			h[i + j].push_back(temp);
		}
	cin >> q;
	for (int i = 0; i < q; i++) cin >> l[i] >> u[i];
	return 1;
}

void Process() {
	for (int i = 0; i < q; i++) {
		int ans = 0;
		for (auto& diag : h) {
			auto x = lower_bound(diag.begin(), diag.end(), l[i]);
			auto y = upper_bound(diag.begin(), diag.end(), u[i]);
			int d = distance(x, y);
			if (d > ans) ans = d;
		}
		cout << ans << "\n";
	}
	cout << "-\n";
}

int main() {
	FASTIO();

	while (Read()) Process();

	return 0;
}