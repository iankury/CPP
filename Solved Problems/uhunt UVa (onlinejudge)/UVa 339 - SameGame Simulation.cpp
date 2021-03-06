#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int R_MAX = 12, C_MAX = 42;
int R, C, sz, ct;
char a[R_MAX][C_MAX];

struct Point { int row, col; };

bool In_Bounds(const Point& p) { return p.row > 0 && p.col > 0 && p.row <= R && p.col <= C; }

bool Empty_Col(int j) {
	for (int i = 1; i <= R; i++) if (a[i][j] != ' ') return 0;
	return 1;
}

void Move_Col(int origin, int target) {
	for (int i = 1; i <= R; i++) {
		a[i][target] = a[i][origin];
		a[i][origin] = ' ';
	}
}

bool Valid(const Point& move) {
	int i = move.row, j = move.col;
	char c = a[i][j];
	if (i > 1 && a[i - 1][j] == c) return 1;
	if (i < R && a[i + 1][j] == c) return 1;
	if (j > 1 && a[i][j - 1] == c) return 1;
	if (j < C && a[i][j + 1] == c) return 1;
	return 0;
}

void Flood_Fill(const Point& target, char key) {
	if (In_Bounds(target) && a[target.row][target.col] == key) {
		sz--;
		a[target.row][target.col] = ' ';
		Flood_Fill({ target.row + 1, target.col }, key);
		Flood_Fill({ target.row - 1, target.col }, key);
		Flood_Fill({ target.row, target.col + 1 }, key);
		Flood_Fill({ target.row, target.col - 1 }, key);
	}
}

void Crumble_Down() {
	if (sz) {
		for (int j = 1; j <= C; j++) {
			vector<char> temp;
			for (int i = R; i; i--)
				if (a[i][j] != ' ') temp.push_back(a[i][j]);
			int k = R;
			for (int i = 0; i < temp.size(); i++, k--) a[k][j] = temp[i];
			for (int i = k; i; i--) a[i][j] = ' ';
		}
	}
}

void Crumble_Left() {
	if (sz) {
		bool empty[12];
		memset(empty, 1, sizeof empty);
		for (int j = 1; j <= C; j++) if (!Empty_Col(j)) empty[j] = 0;
		for (int j = 1; j <= C; j++) {
			if (empty[j]) {
				int first_nonempty = 0;
				for (int k = j + 1; k <= C; k++) {
					if (!empty[k]) {
						first_nonempty = k;
						break;
					}
				}
				if (first_nonempty) {
					Move_Col(first_nonempty, j);
					empty[first_nonempty] = 1;
				}
			}
		}
	}
}

void Process() {
	ct = 0;
	while (cin >> R >> C, R && C) {
		bool won = 0;
		vector<Point> moves;
		sz = R * C;
		for (int i = R; i; i--) 
			for (int j = 1; j <= C; j++) cin >> a[i][j];
		int row_rem, col_rem;
		while (cin >> row_rem >> col_rem, row_rem || col_rem) 
			moves.push_back({ (1 + R - row_rem), col_rem });
		for (auto move : moves) {
			if (In_Bounds(move) && a[move.row][move.col] != ' ' && Valid(move)) {
				Flood_Fill(move, a[move.row][move.col]);
				Crumble_Down();
				Crumble_Left();
				if (!sz) {
					won = 1;
					break;
				}
			}
		}
		if (ct) cout << "\n";
		cout << "Grid " << ++ct << ".\n";
		if (won) cout << "    Game Won\n";
		else {
			for (int i = 1; i <= R; i++) {
				cout << "    ";
				for (int j = 1; j <= C; j++) {
					if (j > 1) cout << " ";
					cout << a[i][j];
				}
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