#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

struct Seg {
	int p, q;
};

vector<Seg> a;

int Next_Left(int idx) {
	if (a[idx].p && a[idx].p != idx) return (a[idx].p = Next_Left(a[idx].p));
	return a[idx].p;
}

int Next_Right(int idx) {
	if (a[idx].q && a[idx].q != idx) return (a[idx].q = Next_Right(a[idx].q));
	return a[idx].q;
}

void Process() {
	int s, b, L, R;
	while (cin >> s >> b, s || b) {
		a.clear();
		a.resize(s + 3);
		a[0].p = a[0].q = 0;
		a[s + 1].p = a[s + 1].q = 0;
		for (int i = 1; i <= s; i++) a[i].p = a[i].q = i;
		for (int i = 0; i < b; i++) {
			cin >> L >> R;
			int x = Next_Left(L - 1), y = Next_Right(R + 1);
			for (int j = L; j <= R; j++) {
				a[j].p = x;
				a[j].q = y;
			}
			if (x) cout << x;
			else cout << "*";
			cout << " ";
			if (y) cout << y;
			else cout << "*";
			cout << "\n";
		}
		cout << "-\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}