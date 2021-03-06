#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 5005, M = 1000000007, BIG = 2147483647;
int n, q;
vi a, l, r;
struct Painter {
	int idx;
	ii score;
	bool operator < (const Painter& x) const { return score < x.score; }
};
vector<Painter> p;

void Process() {
	int chosen = 0;
	cin >> n >> q;
	a.assign(n + 1, 0);
	l.resize(q);
	r.resize(q);
	for (int i = 0; i < q; i++) {
		cin >> l[i] >> r[i];
		for (int j = l[i]; j <= r[i]; j++) a[j]++;
	}
	p.resize(q);
	for (int i = 0; i < q; i++) p[i] = { i, {0, 0} };
	for (int i = 0; i < q; i++) {
		for (int j = l[i]; j <= r[i]; j++) {
			if (a[j] == 1) p[i].score.first++;
			else if (a[j] == 2) p[i].score.second++;
		}
		if (!p[i].score.first && !p[i].score.second) {
			chosen++;
			for (int j = l[i]; j <= r[i]; j++) a[j]--;
			p[i].score.first = BIG;
			if (chosen == 2) break;
		}
	}
	if (chosen < 2) sort(p.begin(), p.end());
	int idx_ch = 0;
	while (chosen < 2) {
		int lo = l[p[idx_ch].idx], hi = r[p[idx_ch].idx];
		for (int i = lo; i <= hi; i++) a[i]--;
		idx_ch++;
		chosen++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) if (a[i] > 0) ans++;
	cout << ans << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}