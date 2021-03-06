#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005;
const char suits[]{ 'D', 'C', 'H', 'S' };
const char values[]{ '2', '3', '4', '5', '6', '7', '8', '9', 
						'T', 'J', 'Q', 'K', 'A' };
const map<string, int> MakeMap() {
	map<string, int> ans;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			string s = "";
			s += suits[i];
			s += values[j];
			ans[s] = i * 13 + j + 1;
		}
	}
	return ans;
}
map<string, int> cards = MakeMap();

int Face(int card) {
	card--;
	card %= 13;
	if (values[card] == 'J') return 1;
	if (values[card] == 'Q') return 2;
	if (values[card] == 'K') return 3;
	if (values[card] == 'A') return 4;
	return 0;
}

void Process() {
	string s;
	while (cin >> s, s != "#") {
		list<int> p1, p2, table;
		bool dealer = 0;
		int debt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				if (i || j) cin >> s;
				if (dealer) p1.push_back(cards[s]);
				else p2.push_back(cards[s]);
				dealer = !dealer;
			}
		}
		dealer = 0;
		while (1) {
			list<int> &player = dealer ? p1 : p2;
			list<int> &enemy = dealer ? p2 : p1;
			if (player.empty()) {
				if (dealer) cout << "2 ";
				else cout << "1 ";
				if (enemy.size() < 10) cout << " ";
				cout << enemy.size() << "\n";
				break;
			}
			int card = player.back();
			player.pop_back();
			table.push_back(card);
			int face = Face(card);
			if (face) {
				debt = face;
				dealer = !dealer;
			}
			else {
				if (debt) {
					debt--;
					if (!debt) {
						while (!table.empty()) {
							int transf = table.front();
							table.pop_front();
							enemy.push_front(transf);
						}
						dealer = !dealer;
					}
				}
				else dealer = !dealer;
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


/*
void DEBUG() {
	cout << "DEBUG" << ":\n";

	cout << "END OF DEBUG\n";
}
//*/