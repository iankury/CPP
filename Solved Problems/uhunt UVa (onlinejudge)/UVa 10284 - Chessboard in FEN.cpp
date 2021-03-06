#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

struct Tile {
	char data;
	bool white;
	Tile() : data('\0'), white(0) {}
	Tile(char c) {
		white = isupper(c);
		data = tolower(c);
	}
};

bool InBounds(int row, int col) {
	return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}

bool Piece(char piece, bool white, int row, int col, const Tile(&t)[8][8]) {
	return InBounds(row, col) ? t[row][col].data == piece && t[row][col].white == white : 0;
}

bool Attacked(bool white, int row, int col, const Tile (&t)[8][8]) {
	if (t[row][col].data) return 1; // will process only empty tiles
	if (white) {
		// black pawns from above
		if (Piece('p', 0, row - 1, col - 1, t)
			|| Piece('p', 0, row - 1, col + 1, t))
			return 1;
	}
	else {
		// white pawns from below
		if (Piece('p', 1, row + 1, col - 1, t)
			|| Piece('p', 1, row + 1, col + 1, t))
			return 1;
	}
	// kings
	if (Piece('k', !white, row, col + 1, t)
		|| Piece('k', !white, row, col - 1, t)
		|| Piece('k', !white, row + 1, col, t)
		|| Piece('k', !white, row - 1, col, t)
		|| Piece('k', !white, row + 1, col + 1, t)
		|| Piece('k', !white, row - 1, col - 1, t)
		|| Piece('k', !white, row - 1, col + 1, t)
		|| Piece('k', !white, row + 1, col - 1, t))
		return 1;
	// knights
	if (Piece('n', !white, row - 1, col - 2, t)
		|| Piece('n', !white, row - 2, col - 1, t)
		|| Piece('n', !white, row - 2, col + 1, t)
		|| Piece('n', !white, row - 1, col + 2, t)
		|| Piece('n', !white, row + 1, col - 2, t)
		|| Piece('n', !white, row + 2, col - 1, t)
		|| Piece('n', !white, row + 2, col + 1, t)
		|| Piece('n', !white, row + 1, col + 2, t))
		return 1;
	// bishops and partially queens
	// first non-empty from top-left
	int r1 = row - 1, c1 = col - 1;
	while (InBounds(r1, c1) && !t[r1][c1].data) {
		r1--;
		c1--;
		
	}
	// first non-empty from top-right
	int r2 = row - 1, c2 = col + 1;
	while (InBounds(r2, c2) && !t[r2][c2].data) {
		r2--;
		c2++;
	}
	// first non-empty from bottom-left
	int r3 = row + 1, c3 = col - 1;
	while (InBounds(r3, c3) && !t[r3][c3].data) {
		r3++;
		c3--;
	}
	// first non-empty from bottom-right
	int r4 = row + 1, c4 = col + 1;
	while (InBounds(r4, c4) && !t[r4][c4].data) {
		r4++;
		c4++;
	}
	if (Piece('b', !white, r1, c1, t)
		|| Piece('q', !white, r1, c1, t)
		|| Piece('b', !white, r2, c2, t)
		|| Piece('q', !white, r2, c2, t)
		|| Piece('b', !white, r3, c3, t)
		|| Piece('q', !white, r3, c3, t)
		|| Piece('b', !white, r4, c4, t)
		|| Piece('q', !white, r4, c4, t))
		return 1;
	// rooks and partially queens
	// first non-empty from top
	r1 = row - 1, c1 = col;
	while (InBounds(r1, c1) && !t[r1][c1].data) r1--;
	// first non-empty from bottom
	r2 = row + 1, c2 = col;
	while (InBounds(r2, c2) && !t[r2][c2].data) r2++;
	// first non-empty from left
	r3 = row, c3 = col - 1;
	while (InBounds(r3, c3) && !t[r3][c3].data) c3--;
	// first non-empty from right
	r4 = row, c4 = col + 1;
	while (InBounds(r4, c4) && !t[r4][c4].data) c4++;
	if (Piece('r', !white, r1, c1, t)
		|| Piece('q', !white, r1, c1, t)
		|| Piece('r', !white, r2, c2, t)
		|| Piece('q', !white, r2, c2, t)
		|| Piece('r', !white, r3, c3, t)
		|| Piece('q', !white, r3, c3, t)
		|| Piece('r', !white, r4, c4, t)
		|| Piece('q', !white, r4, c4, t))
		return 1;
	return 0;
}

void Process() {
	while (1) {
		Tile t[8][8];
		{
			string s;
			getline(cin, s);
			int i = 0, j = 0, k = 0;
			while (k < s.size()) {
				if (j == 8) {
					j = 0;
					i++;
				}
				if (isdigit(s[k])) {
					int q = s[k] - '0';
					j += q;
				}
				else if (isalpha(s[k])) {
					t[i][j] = Tile(s[k]);
					j++;
				}
				k++;
			}
		}
		int ans = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (!Attacked(1, i, j, t) && !Attacked(0, i, j, t)) ans++;
		cout << ans << "\n";
		if (!isalnum(cin.peek())) break;
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}