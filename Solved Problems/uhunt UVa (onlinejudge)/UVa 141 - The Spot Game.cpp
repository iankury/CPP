#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct Move { int row, col; char action; };
class Matrix {
	int sz;
	string s, cw, ccw;
public:
	Matrix(int n) : sz(n) { 
		s.resize(n * n); 
		cw.resize(n * n);
		ccw.resize(n * n);
		for (int i = 0; i < s.length(); i++) s[i] = cw[i] = ccw[i] = '0';
	}
	bool Play(Move* move, set<string>& matrices) {
		int row = move->row - 1, col = move->col - 1;
		int index[]{ row * sz + col, col * sz + sz - 1 - row, (sz - 1 - col) * sz + row };
		if (move->action == '+') s[index[0]] = cw[index[1]] = ccw[index[2]] = '1';
		else s[index[0]] = cw[index[1]] = ccw[index[2]] = '0';
		if (matrices.count(s) || matrices.count(cw) || matrices.count(ccw)) return 0;
		matrices.insert({ s, cw, ccw });
		return 1;
	}
};

void Process() {
	int n;
	while (cin >> n, n) {
		set<string> matrices;
		vector<Move> moves;
		moves.resize(2 * n);
		for (int i = 0; i < moves.size(); i++) 
			cin >> moves[i].col >> moves[i].row >> moves[i].action;
		Matrix matrix(n);
		int player = 1;
		bool done = 0;
		for (int i = 0; i < moves.size() && !done; i++) {
			player = player == 1 ? 2 : 1;
			if (!matrix.Play(&moves[i], matrices)) {
				cout << "Player " << player << " wins on move " << i + 1 << "\n";
				done = 1;
			}
		}
		if (done) continue;
		cout << "Draw\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}