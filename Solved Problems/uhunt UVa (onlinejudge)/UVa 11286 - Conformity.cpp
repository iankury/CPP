#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef unsigned long long ull;
typedef unsigned short us;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;
int n;
map<set<us>, int> s;

void Process() {
	while (cin >> n, n) {
		s.clear();
		for (int i = 0; i < n; i++) {
			us x;
			set<us> r;
			for (int j = 0; j < 5; j++) {
				cin >> x;
				r.insert(x);
			}
			s[r]++;
		}
		int max = 0, ans = 0;
		for (auto& k : s) {
			if (k.second > max) max = k.second, ans = 0;
			if (k.second == max) ans += max;
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