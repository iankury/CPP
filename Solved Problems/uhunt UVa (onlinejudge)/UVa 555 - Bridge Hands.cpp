#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int NN = 100005, M = 1000000007;

struct Card {
	char suit, value;
	int priority;
	Card(char s, char v) : suit(s), value(v) {
		priority = 0;
		if (s == 'D') priority += 1000;
		if (s == 'S') priority += 2000;
		if (s == 'H') priority += 3000;
		if (v >= '2' && v <= '9') priority += v - '0';
		if (v == 'T') priority += 10;
		if (v == 'J') priority += 11;
		if (v == 'Q') priority += 12;
		if (v == 'K') priority += 13;
		if (v == 'A') priority += 14;
	}
	bool operator < (const Card& a) { return priority < a.priority; }
	string Print() { string s = ""; s += suit; s += value; return s; }
};

enum { N, E, S, W };

int Encode(char c) {
	switch (c) {
	case 'N': return N;
	case 'E': return E;
	case 'S': return S;
	case 'W': return W;
	default: return -1;
	}
}

class Game {
	vector<Card> hands[4];
	int cur;
public:
	Game(int dealer) : cur(dealer) {}
	vector<Card>& Next() {
		cur = (cur + 1) % 4;
		return hands[cur];
	}
	void Deal(const Card& card) {
		vector<Card>& receiver = Next();
		receiver.push_back(card);
	}
	string Print(vector<Card>& hand) {
		string s = "";
		for (int i = 0; i < hand.size(); i++) {
			if (i) s += " ";
			s += hand[i].Print();
		}
		return s;
	}
	void Print() {
		for (int i = 0; i < 4; i++) sort(hands[i].begin(), hands[i].end());
		cout << "S: " << Print(hands[S]);
		cout << "\nW: " << Print(hands[W]);
		cout << "\nN: " << Print(hands[N]);
		cout << "\nE: " << Print(hands[E]);;
		cout << "\n";
	}
};

void Process() {
	char c;
	while (cin >> c, c != '#') {
		Game game(Encode(c));
		int i = 52;
		while (i--) {
			char s, v;
			cin >> s >> v;
			Card card(s, v);
			game.Deal(Card(s, v));
		}
		game.Print();
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