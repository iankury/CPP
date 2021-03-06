#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct Card {
	char value, suit;
};

class Hand {
	vector<Card> cards;
	int D, C, H, S, points_to_4;
public:
	char largest;
	Hand() : largest('\0') {}
	bool Initialized() { return largest; }
	void Read(const string &s) {
		for (int i = 1; i < s.length(); i += 3)
			cards.push_back(Card{ s[i - 1], s[i] });
	}
	int Count(char suit) {
		if (Initialized()) {
			switch (suit) {
			case 'D': return D;
			case 'C': return C;
			case 'H': return H;
			case 'S': return S;
			}
		}
		int ans = 0;
		for (int i = 0; i < cards.size(); i++)
			if (cards[i].suit == suit) ans++;
		return ans;
	}
	bool Contains(char value, char suit) {
		for (int i = 0; i < cards.size(); i++)
			if (cards[i].value == value && cards[i].suit == suit) return 1;
		return 0;
	}
	bool Stopped(char suit) {
		return (Contains('A', suit) || (Contains('K', suit) && Count(suit) > 1) ||
			(Contains('Q', suit) && Count(suit) > 2));
	}
	bool Stopped() {
		return (Stopped('S') && Stopped('H') && Stopped('D') && Stopped('C'));
	}
	int Points_to_4() {
		int ans = 0;
		for (int i = 0; i < cards.size(); i++) {
			if (cards[i].value == 'A') ans += 4;
			if (cards[i].value == 'K')
				ans = (Count(cards[i].suit) == 1) ? ans + 2 : ans + 3;
			if (cards[i].value == 'Q')
				ans = (Count(cards[i].suit) <= 2) ? ans + 1 : ans + 2;
			if (cards[i].value == 'J')
				ans = (Count(cards[i].suit) <= 3) ? ans : ans + 1;
		}
		return ans;
	}
	bool No_Trump() {
		return (Stopped() && (points_to_4 >= 16));
	}
	int Points(char suit) {
		if (Count(suit) == 2) return 1;
		if (Count(suit) < 2) return 2;
		return 0;
	}
	int Points() {
		return points_to_4 + Points('D') + Points('S') + Points('H') + Points('C');
	}
	char Max_Suit() {
		int max_freq = S;
		char ans = 'S';
		if (H > max_freq) { max_freq = H; ans = 'H'; }
		if (D > max_freq) { max_freq = D; ans = 'D'; }
		if (C > max_freq) return 'C';
		return ans;
	}
	void Initialize() {
		D = Count('D');
		C = Count('C');
		H = Count('H');
		S = Count('S');
		largest = Max_Suit();
		points_to_4 = Points_to_4();
	}
};

void Process() {
	string s;
	while (getline(cin, s)) {
		if (s.size() < 20) break;
		Hand hand;
		hand.Read(s);
		hand.Initialize();
		if (hand.No_Trump()) cout << "BID NO-TRUMP\n";
		else if (hand.Points() > 13) cout << "BID " << hand.largest << "\n";
		else cout << "PASS\n";
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