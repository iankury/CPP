#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

map<char, int> Worth{ {'T', 10}, {'J', 11} , {'Q', 12} , {'K', 13} , {'A', 14} };
enum { HIGH_CARD, PAIR, TWO_PAIRS, THREE, STRAIGHT, FLUSH, FULL_HOUSE, FOUR, STRAIGHT_FLUSH};

struct Card {
	char value, suit;
	int worth;
	Card(char v, char s) : value(v), suit(s) { worth = Worth[v]; }
	bool operator < (const Card& card) { return worth < card.worth; }
};

bool Flush(const vector<Card> hand) {
	char suit = hand[0].suit;
	for (int i = 1; i < 5; i++) if (hand[i].suit != suit) return 0;
	return 1;
}

bool Straight(const vector<Card> hand) {
	for (int i = 1; i < 5; i++) if (hand[i].worth != hand[i - 1].worth + 1) return 0;
	return 1;
}

int* Repetidas(const vector<Card>& hand, int times) {
	int* ans = new int[4] { 0, 0, 0, 0 };
	int freq[15];
	memset(freq, 0, sizeof freq);
	for (int i = 0; i < 5; i++) freq[hand[i].worth]++;
	for (int i = 1; i < 15; i++) {
		if (freq[i] == times) {
			if (ans[0]) ans[1] = i;
			else ans[0] = i;
		}
	}
	if (ans[0]) {
		for (int i = 1; i < 15; i++) {
			if (freq[i] == 1) {
				for (int j = 1; j < 4; j++) {
					if (ans[j]) continue;
					ans[j] = i;
					break;
				}
			}
		}
		return ans;
	}
	delete ans;
	return 0;
}

class Hand {
	vector<Card> cards;
	string name;
public:
	vector<int> desempate;
	int jogada;
	Hand(const string& n, const string& s) : name(n) {
		for (int i = 0; i < 13; i += 3) {
			Card card(s[i], s[i + 1]);
			cards.push_back(card);
		}
		sort(cards.begin(), cards.end());
		bool flush = Flush(cards), straight = Straight(cards);
		if (flush && straight) {
			jogada = STRAIGHT_FLUSH;
			for (int i = 4; i >= 0; i--) desempate.push_back(cards[i].worth);
			return;
		}
		int* F = Repetidas(cards, 4);
		if (F) {
			jogada = FOUR;
			desempate.push_back(F[0]);
			delete F;
			return;
		}
		delete F;
		int* T = Repetidas(cards, 3), * P = Repetidas(cards, 2);
		if (T && P) {
			jogada = FULL_HOUSE;
			for (int i = 4; i >= 0; i--) desempate.push_back(T[0]);
			delete T, P;
			return;
		}
		if (flush) {
			jogada = FLUSH;
			for (int i = 4; i >= 0; i--) desempate.push_back(cards[i].worth);
			delete T, P;
			return;
		}
		if (straight) {
			jogada = STRAIGHT;
			desempate.push_back(cards[4].worth);
			delete T, P;
			return;
		}
		if (T) {
			jogada = THREE;
			desempate.push_back(T[0]);
			delete T, P;
			return;
		}
		delete T;
		if (P) {
			if (P[3]) {
				jogada = PAIR;
				desempate.push_back(P[0]);
				desempate.push_back(P[3]);
				desempate.push_back(P[2]);
				desempate.push_back(P[1]);
			}
			else {
				jogada = TWO_PAIRS;
				desempate.push_back(P[1]);
				desempate.push_back(P[0]);
				desempate.push_back(P[2]);
			}
			delete P;
			return;
		}
		delete P;
		jogada = HIGH_CARD;
		for (int i = 4; i >= 0; i--) desempate.push_back(cards[i].worth);
	}
	void Wins() {
		cout << name << " wins.\n";
	}
};

void Process() {
	for (char i = '2'; i <= '9'; i++) Worth[i] = i - '0';
	string s1, s2;
	while (getline(cin, s1), s1 != "") {
		s2 = s1.substr(15, s1.size());
		s1 = s1.substr(0, 14);
		Hand black("Black", s1), white("White", s2);
		if (black.jogada > white.jogada) black.Wins();
		else if (black.jogada < white.jogada) white.Wins();
		else {
			for (int i = 0; i < black.desempate.size(); i++) {
				if (black.desempate[i] > white.desempate[i]) {
					black.Wins();
					break;
				}
				else if (black.desempate[i] < white.desempate[i]) {
					white.Wins();
					break;
				}
				else if (i == black.desempate.size() - 1) cout << "Tie.\n";
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