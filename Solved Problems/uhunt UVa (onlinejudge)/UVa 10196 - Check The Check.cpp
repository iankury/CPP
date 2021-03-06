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
string s[8];
struct Point { int row, col; };

bool InBounds(const Point& p) {
	return (p.row >= 0 && p.row < 8 && p.col >= 0 && p.col < 8);
}

bool Piece(char piece, const Point& p) {
	return InBounds(p) ? (s[p.row][p.col] == piece) : 0;
}

void Process() {
	int ct = 1;
	while (1) {
		for (int i = 0; i < 8; i++) cin >> s[i];
		Point king{ -1, -1 }, King{ -1, -1 };
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (s[i][j] == 'k') {
					king.row = i;
					king.col = j;
				}
				else if (s[i][j] == 'K') {
					King.row = i;
					King.col = j;
				}
			}
		}
		if (king.row >= 0) {
			cout << "Game #" << ct << ": ";
			ct++;
			// White king
			// check if any black piece is attacking
			// check for pawns (from above) and black knights
			int r = King.row, c = King.col;
			if (Piece('p', { r - 1, c - 1 })
				|| Piece('p', { r - 1, c + 1 })
				|| Piece('n', { r - 1, c - 2 })
				|| Piece('n', { r - 2, c - 1 })
				|| Piece('n', { r - 2, c + 1 })
				|| Piece('n', { r - 1, c + 2 })
				|| Piece('n', { r + 1, c - 2 })
				|| Piece('n', { r + 2, c - 1 })
				|| Piece('n', { r + 2, c + 1 })
				|| Piece('n', { r + 1, c + 2 })) {
				cout << "white king is in check.\n";
				continue;
			}
			// check for bishops (and partially queens)
			Point p1, p2, p3, p4; // first not empty in each direction
			// top left
			p1 = { r - 1, c - 1 };
			while (Piece('.', p1)) {
				p1.col--;
				p1.row--;
			}
			// top right
			p2 = { r - 1, c + 1 };
			while (Piece('.', p2)) {
				p2.col++;
				p2.row--;
			}
			// bottom left
			p3 = { r + 1, c - 1 };
			while (Piece('.', p3)) {
				p3.col--;
				p3.row++;
			}
			// bottom right
			p4 = { r + 1, c + 1 };
			while (Piece('.', p4)) {
				p4.col++;
				p4.row++;
			}
			if (Piece('b', p1) || Piece('q', p1) || 
				Piece('b', p2) || Piece('q', p2) || 
				Piece('b', p3) || Piece('q', p3) || 
				Piece('b', p4) || Piece('q', p4)) {
				cout << "white king is in check.\n";
				continue;
			}
			// check for rooks (and partially queens)
			// top
			p1 = { r - 1, c };
			while (Piece('.', p1)) p1.row--;
			// bottom
			p2 = { r + 1, c };
			while (Piece('.', p2)) p2.row++;
			// left
			p3 = { r, c - 1 };
			while (Piece('.', p3)) p3.col--;
			// right
			p4 = { r, c + 1 };
			while (Piece('.', p4)) p4.col++;
			if (Piece('r', p1) || Piece('q', p1) ||
				Piece('r', p2) || Piece('q', p2) ||
				Piece('r', p3) || Piece('q', p3) ||
				Piece('r', p4) || Piece('q', p4)) {
				cout << "white king is in check.\n";
				continue;
			}
			// Black king
			// check if any white piece is attacking
			// check for pawns (from below) and white knights
			r = king.row, c = king.col;
			if (Piece('P', { r + 1, c - 1 })
				|| Piece('P', { r + 1, c + 1 })
				|| Piece('N', { r - 1, c - 2 })
				|| Piece('N', { r - 2, c - 1 })
				|| Piece('N', { r - 2, c + 1 })
				|| Piece('N', { r - 1, c + 2 })
				|| Piece('N', { r + 1, c - 2 })
				|| Piece('N', { r + 2, c - 1 })
				|| Piece('N', { r + 2, c + 1 })
				|| Piece('N', { r + 1, c + 2 })) {
				cout << "black king is in check.\n";
				continue;
			}
			// check for bishops (and partially queens)
			// top left
			p1 = { r - 1, c - 1 };
			while (Piece('.', p1)) {
				p1.col--;
				p1.row--;
			}
			// top right
			p2 = { r - 1, c + 1 };
			while (Piece('.', p2)) {
				p2.col++;
				p2.row--;
			}
			// bottom left
			p3 = { r + 1, c - 1 };
			while (Piece('.', p3)) {
				p3.col--;
				p3.row++;
			}
			// bottom right
			p4 = { r + 1, c + 1 };
			while (Piece('.', p4)) {
				p4.col++;
				p4.row++;
			}
			if (Piece('B', p1) || Piece('Q', p1) ||
				Piece('B', p2) || Piece('Q', p2) ||
				Piece('B', p3) || Piece('Q', p3) ||
				Piece('B', p4) || Piece('Q', p4)) {
				cout << "black king is in check.\n";
				continue;
			}
			// check for rooks (and partially queens)
			// top
			p1 = { r - 1, c };
			while (Piece('.', p1)) p1.row--;
			// bottom
			p2 = { r + 1, c };
			while (Piece('.', p2)) p2.row++;
			// left
			p3 = { r, c - 1 };
			while (Piece('.', p3)) p3.col--;
			// right
			p4 = { r, c + 1 };
			while (Piece('.', p4)) p4.col++;
			if (Piece('R', p1) || Piece('Q', p1) ||
				Piece('R', p2) || Piece('Q', p2) ||
				Piece('R', p3) || Piece('Q', p3) ||
				Piece('R', p4) || Piece('Q', p4)) {
				cout << "black king is in check.\n";
				continue;
			}
			cout << "no king is in check.\n";
		}
		else break;
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}