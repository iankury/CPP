#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
unsigned int n, m, l, u;

bool Read() {
	cin >> n;
	if (cin.eof()) return 0;
	cin >> l >> u;

	return 1;
}

void Process() {
	m = u;
	unsigned int past = 0;
	bool credit = 0;
	for (int i = 31; i >= 0; i--) {
		int p = ((1 << i) - 1) + past;
		if (!(m & (1 << i)) && credit) {
			if (p < l || !(n & (1 << i))) m += (1 << i);
		}
		else if ((m & (1 << i)) && (n & (1 << i))) {
			if (p >= l) {
				credit = 1;
				m -= (1 << i);
			}
		}
		if (m & (1 << i)) past += (1 << i);
	}
	
	cout << m << "\n";
}

int main() {
	FASTIO();

	while (Read()) Process();

	return 0;
}