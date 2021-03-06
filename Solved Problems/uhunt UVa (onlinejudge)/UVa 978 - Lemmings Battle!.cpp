#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 101, M = 1000000007;

int g[N], b[N], fields, green, blue, x, mg, mb;
bool virgin = 1;

void Update_Max() {
	int j = mg;
	for (; j; j--) if (g[j]) break;
	mg = j;
	j = mb;
	for (; j; j--) if (b[j]) break;
	mb = j;
}

void Process() {
	if (virgin) virgin = 0;
	else cout << "\n";
	mg = mb = 0;
	cin >> fields >> green >> blue;
	memset(g, 0, sizeof g);
	memset(b, 0, sizeof b);
	for (int i = 0; i < green; i++) {
		cin >> x;
		if (x > mg) mg = x;
		g[x]++;
	}
	for (int i = 0; i < blue; i++) {
		cin >> x;
		if (x > mb) mb = x;
		b[x]++;
	}
	while (mb && mg) {
		vector<int> wb, wg;
		for (int i = 0; i < fields; i++) {
			if (!mb || !mg) break;
			b[mb]--;
			g[mg]--;
			if (mb > mg) wb.push_back(mb - mg);
			else if (mb < mg) wg.push_back(mg - mb);
			Update_Max();
		}
		for (auto& y : wg) g[y]++;
		for (auto& y : wb) b[y]++;
		mb = mg = 100;
		Update_Max();
	}
	if (!(mb || mg)) cout << "green and blue died\n";
	else if (mb) {
		cout << "blue wins\n";
		for (int i = 100; i; i--) while (b[i]--) cout << i << "\n";
	}
	else {
		cout << "green wins\n";
		for (int i = 100; i; i--) while (g[i]--) cout << i << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}