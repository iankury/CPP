#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 102, M = 1000000007;
int ct, n, m;
char a[N][N];

bool In_Bounds(int row, int col) {
	return !(row < 0 || row > n || col < 0 || col > m);
}

void Add(int row, int col) {
	if (In_Bounds(row, col))
		if (a[row][col] != '*') a[row][col]++;
}

void Process() {
	ct = 1;
	while (cin >> n >> m, m) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a[i][j];
				if (a[i][j] == '.') a[i][j] = '0';
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i][j] == '*') {
					Add(i - 1, j - 1);
					Add(i - 1, j);
					Add(i - 1, j + 1);
					Add(i, j - 1);
					Add(i, j + 1);
					Add(i + 1, j - 1);
					Add(i + 1, j);
					Add(i + 1, j + 1);
				}
			}
		}
		if (ct > 1) cout << "\n";
		cout << "Field #" << ct << ":\n";
		ct++;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << a[i][j];
			cout << "\n";
		}
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}