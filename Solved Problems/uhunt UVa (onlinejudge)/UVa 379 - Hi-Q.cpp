#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;
const int BOARD[7][7]{ 
{0, 0, 1, 2, 3, 0, 0},
{0, 0, 4, 5, 6, 0, 0},
{7, 8, 9, 10, 11, 12, 13},
{14, 15, 16, 17, 18, 19, 20},
{21, 22, 23, 24, 25, 26, 27},
{0, 0, 28, 29, 30, 0, 0},
{0, 0, 31, 32, 33, 0, 0} };

enum { ABOVE, BELOW, LEFT, RIGHT };

struct Jump {
	int origin, victim, target;
	bool operator < (const Jump& p) const {
		return ((origin + (target * 10000)) < (p.origin + (p.target * 10000)));
	}
};

struct Node {
	bool peg;
	int key;
	Node* Neib[4];
	Node() : peg(0) { for (int i = 0; i < 4; i++) Neib[i] = 0; }
};

void Build_Graph(vector<Node*>& a) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			int x = BOARD[i][j];
			if (x) {
				a[x]->key = x;
				if (i && BOARD[i - 1][j]) a[x]->Neib[ABOVE] = a[BOARD[i - 1][j]];
				if (i < 6 && BOARD[i + 1][j]) a[x]->Neib[BELOW] = a[BOARD[i + 1][j]];
				if (j && BOARD[i][j - 1]) a[x]->Neib[LEFT] = a[BOARD[i][j - 1]];
				if (j < 6 && BOARD[i][j + 1]) a[x]->Neib[RIGHT] = a[BOARD[i][j + 1]];
			}
		}
	}
}

void Add_Jump(set<Jump>& jumps, Node* node) {
	if (!node || !node->peg) return;
	for (int i = 0; i < 4; i++) {
		if (node->Neib[i] && node->Neib[i]->peg &&
			node->Neib[i]->Neib[i] && !node->Neib[i]->Neib[i]->peg)
			jumps.insert({ node->key, node->Neib[i]->key, node->Neib[i]->Neib[i]->key });
	}
}

void Process() {
	vector<Node*> nodes;
	for (int i = 0; i < 34; i++) nodes.push_back(new Node);
	Build_Graph(nodes);
	int ans = 0;
	int x;
	while (cin >> x, x) nodes[x]->peg = 1;
	set<Jump> possible_jumps;
	for (auto node : nodes) Add_Jump(possible_jumps, node);
	while (possible_jumps.size()) {
		Jump max = *possible_jumps.rbegin();
		nodes[max.origin]->peg = 0;
		nodes[max.victim]->peg = 0;
		nodes[max.target]->peg = 1;
		possible_jumps.clear();
		for (auto node : nodes) Add_Jump(possible_jumps, node);
	}
	for (auto node : nodes) if (node->peg) ans += node->key;
	cout << ans << "\n";
}

int main() {
	FASTIO();

	cout << "HI Q OUTPUT\n";
	int T = 1;
	cin >> T;
	while (T--) Process();
	cout << "END OF OUTPUT\n";

	return 0;
}