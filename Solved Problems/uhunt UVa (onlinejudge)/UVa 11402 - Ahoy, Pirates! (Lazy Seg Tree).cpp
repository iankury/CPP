#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;
typedef vector<int> vi;

const int N = (1 << 20), M = 3 * (1 << 20);

int ct = 0, n;
bitset<N> a;
char lazy[M];
int st[M];

void Build(int p, int L, int R) {
	lazy[p] = 'N';
	if (L == R) {
		st[p] = a[L];
		return;
	}
	int mid = L + (R - L) / 2, l = (p << 1), r = l + 1;
	Build(l, L, mid);
	Build(r, mid + 1, R);
	st[p] = st[l] + st[r];
}

void Update_Node(int p, int L, int R, char act) {
	if (act == 'N') return;
	if (act == 'F') st[p] = R - L + 1;
	else if (act == 'E') st[p] = 0;
	else if (act == 'I') st[p] = (R - L + 1) - st[p];
	int	ch = (p << 1);
	if (act == 'I') {
		for (int i = 0; i < 2; i++, ch++) {
			if (lazy[ch] == 'F') lazy[ch] = 'E';
			else if (lazy[ch] == 'E') lazy[ch] = 'F';
			else if (lazy[ch] == 'I') lazy[ch] = 'N';
			else lazy[ch] = 'I';
		}
	}
	else lazy[ch] = lazy[ch + 1] = act;
}

void Propagate(int p, int L, int R) {
	if (lazy[p] == 'N') return;
	Update_Node(p, L, R, lazy[p]);
	lazy[p] = 'N';
}

int Q(int p, int L, int R, int i, int j) {
	if (R < i || L > j) return 0;
	if (L <= i && R >= j) {
		if (lazy[p] == 'F') return j - i + 1;
		if (lazy[p] == 'E') return 0;
	}
	Propagate(p, L, R);
	if (L >= i && R <= j) return st[p];
	int mid = L + (R - L) / 2, l = (p << 1), r = l + 1;
	int p1 = Q(l, L, mid, i, j), p2 = Q(r, mid + 1, R, i, j);
	return p1 + p2;
}

void Convert(int p, int L, int R, int i, int j, char act) {
	Propagate(p, L, R);
	if (R < i || L > j) return;
	if (L >= i && R <= j) Update_Node(p, L, R, act);
	else {
		int mid = L + (R - L) / 2, l = (p << 1), r = l + 1;
		Convert(l, L, mid, i, j, act);
		Convert(r, mid + 1, R, i, j, act);
		st[p] = st[l] + st[r];
	}
}

void Process() {
	int q_ct = 0, m, t, q, x, y;
	n = 0;
	char c;
	string s;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> t >> s;
		for (int k = 0; k < t; k++)
			for (int j = 0; j < s.length(); j++, n++) a[n] = s[j] == '1';
	}
	Build(1, 0, n - 1);
	cin >> q;
	cout << "Case " << ++ct << ":\n";
	for (int i = 0; i < q; i++) {
		cin >> c >> x >> y;
		if (c == 'S') cout << "Q" << ++q_ct << ": " << Q(1, 0, n - 1, x, y) << "\n";
		else Convert(1, 0, n - 1, x, y, c);
	}
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}