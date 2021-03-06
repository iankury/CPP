#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007;
int mat[11][11], mat_R[11][11], mat_D[11][11], odd_mat[21][21];
int freq[N], n, m;

struct Point { 
	int r, c, side;
	void Next() {
		c++;
		if (c > side) {
			c = 1;
			r++;
		}
	}
};

struct Position {
	bool middle;
	int MID;
	int row, col, ref, dir; // 1 = Up left, 2 = Up Right, 3 = Bot Right, 4 = Bot Left, UDLR
	Position() : dir(1), middle(0) {
		MID = n / 2 + 1;
		ref = row = col = MID - 1;
	}
	void Next() {
		if (middle) {
			if (dir == 1) {
				int dis = MID - row;
				row += 2 * dis;
			}
			else if (dir == 2) {
				int dis = row - MID;
				row -= dis;
				col -= dis;
			}
			else if (dir == 3) {
				int dis = MID - col;
				col += 2 * dis;
			}
			else if (dir == 4) {
				int dis = col - MID;
				col -= dis;
				row -= (1 + dis);
			}
		}
		else {
			if (dir == 1) {
				int dis = MID - col;
				col += 2 * dis;
			}
			else if (dir == 2) {
				int dis = MID - row;
				row += 2 * dis;
			}
			else if (dir == 3) {
				int dis = col - MID;
				col -= 2 * dis;
			}
			else if (dir == 4) {
				int dis = row - MID;
				if (dis == 1) {
					ref--;
					row = col = ref;
				}
				else {
					row -= 2 * dis;
					row++;
				}
			}
		}
		dir++;
		if (dir == 5) dir = 1;
	}
};

void Process() {
	memset(freq, 0, sizeof freq);
	cin >> n;
	m = n * n;
	int x;
	if (n == 1) {
		cin >> x;
		cout << "YES\n";
		cout << x << "\n";
		return;
	}
	bool fail = 0, virgin = 1;
	for (int i = 0; i < m; i++) {
		cin >> x;
		freq[x]++;
	}
	if (n % 2) { // ODD
		for (int i = 1; i < 1001; i++) {
			if (freq[i] % 2) {
				if (virgin) {
					virgin = 0;
					freq[i]--;
					odd_mat[n / 2 + 1][n / 2 + 1] = i;
				}
				else {
					fail = 1;
					break;
				}
			}
		}
		if (virgin || fail) cout << "NO\n";
		else {
			Position p;
			for (int i = 1; i < 1001; i++) {
				while (freq[i] > 3) {
					freq[i] -= 4;
					for (int j = 0; j < 4; j++) {
						odd_mat[p.row][p.col] = i;
						p.Next();
					}
					if (p.row < 1) {
						p.middle = 1;
						p.row = p.MID - 1;
						p.col = p.MID;
						p.dir = 1;
					}
				}
			}
			if (!p.middle) cout << "NO\n";
			else {
				for (int i = 1; i < 1001; i++) {
					while (freq[i] > 1) {
						if (p.row < 1) {
							cout << "NO\n";
							return;
						}
						freq[i] -= 2;
						for (int j = 0; j < 2; j++) {
							odd_mat[p.row][p.col] = i;
							p.Next();
						}
					}
				}
				cout << "YES\n";
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) cout << odd_mat[i][j] << " ";
					cout << "\n";
				}
			}
		}
	}
	else { // EVEN
		for (int i = 1; i < 1001; i++) {
			if (freq[i] % 4) {
				fail = 1;
				break;
			}
			freq[i] /= 4;
		}
		if (fail) cout << "NO\n";
		else {
			cout << "YES\n";
			Point cur{ 1, 1, n / 2 };
			for (int i = 1; i < 1001; i++) {
				if (freq[i]) {
					mat[cur.r][cur.c] = i;
					freq[i]--;
					i--;
					cur.Next();
				}
			}
			for (int j = 1; j <= cur.side; j++) 
				for (int i = 1; i <= cur.side; i++) mat_R[i][j] = mat[i][cur.side - j + 1];
			for (int i = 1; i <= cur.side; i++) {
				for (int j = 1; j <= cur.side; j++) cout << mat[i][j] << " ";
				for (int j = 1; j <= cur.side; j++) cout << mat_R[i][j] << " ";
				cout << "\n";
			}
			for (int i = 1; i <= cur.side; i++)
				for (int j = 1; j <= cur.side; j++) mat_D[i][j] = mat[cur.side - i + 1][j];
			for (int j = 1; j <= cur.side; j++)
				for (int i = 1; i <= cur.side; i++) mat_R[i][j] = mat_D[i][cur.side - j + 1];
			for (int i = 1; i <= cur.side; i++) {
				for (int j = 1; j <= cur.side; j++) cout << mat_D[i][j] << " ";
				for (int j = 1; j <= cur.side; j++) cout << mat_R[i][j] << " ";
				cout << "\n";
			}
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