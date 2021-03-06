#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;
typedef vector<int> vi;

const int N = 11, M = 1000000007, BIG = 0x3f3f3f3f;

int n, a[11], digits[10]{ 126, 48, 109, 121, 51, 91, 95, 112, 127, 123 };

bool Could_Be(int candid, int target) {
	for (int i = 0; i < 7; i++)
		if ((candid & (1 << i)) && !(target & (1 << i))) return 0;
	return 1;
}

bool No_Forbid(int candid, int forbid) {
	for (int i = 0; i < 7; i++)
		if ((candid & (1 << i)) && (forbid & (1 << i))) return 0;
	return 1;
}

int Dif(int candid, int target) {
	int ans = 0;
	for (int i = 0; i < 7; i++)
		if (!(candid & (1 << i)) && (target & (1 << i))) ans |= (1 << i);
	return ans;
}

bool RB(int idx_dig, int idx_a, int forbid, bool running) {
	if (idx_a == n) return 1;
	if (idx_dig < 0) return 0;
	if (!running && RB(idx_dig - 1, idx_a, forbid, 0)) return 1;
	int cur_a = a[idx_a], cur_d = digits[idx_dig];
	if (Could_Be(cur_a, cur_d) && No_Forbid(cur_a, forbid)) {
		forbid |= Dif(cur_a, cur_d);
		return RB(idx_dig - 1, idx_a + 1, forbid, 1);
	}
	return 0;
}

void Process() {
	while (cin >> n, n) {
		string s;
		for (int i = 0; i < n; i++) {
			cin >> s;
			a[i] = 0;
			for (int j = s.length() - 1; j >= 0; j--)
				if (s[j] == 'Y') a[i] |= (1 << (s.length() - 1 - j));
		}
		if (RB(9, 0, 0, 0)) cout << "MATCH\n";
		else cout << "MISMATCH\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}