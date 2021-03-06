#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 103, M = 1000000007;

char a[N][N], b[N][N];

void Process() {
	int n, m;
	while (cin >> n >> m, m) {
		int ans[4]{ 0 };
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> a[i][j];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				cin >> b[i][j];
		for (int r = 0; r + m <= n; r++) {
			for (int c = 0; c + m <= n; c++) {
				bool fail = 0;
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < m; j++) {
						if (a[r + i][c + j] != b[i][j]) {
							fail = 1;
							break;
						}
					}
					if (fail) break;
				}
				if (!fail) ans[0]++;
				fail = 0;
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < m; j++) {
						if (a[r + i][c + j] != b[m - 1 - j][i]) {
							fail = 1;
							break;
						}
					}
					if (fail) break;
				}
				if (!fail) ans[1]++;
				fail = 0;
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < m; j++) {
						if (a[r + i][c + j] != b[m - 1 - i][m - 1 - j]) {
							fail = 1;
							break;
						}
					}
					if (fail) break;
				}
				if (!fail) ans[2]++;
				fail = 0;
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < m; j++) {
						if (a[r + i][c + j] != b[j][m - 1 - i]) {
							fail = 1;
							break;
						}
					}
					if (fail) break;
				}
				if (!fail) ans[3]++;
			}
		}
		cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}