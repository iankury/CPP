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
bool ct;
map<char, int> v_pri{ {'2', 2} , {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7} ,
{'8', 8} , {'9', 9} , {'T', 10} , {'J', 11} , {'Q', 12} , {'K', 13}, {'A', 14} };
map<char, int> s_pri{ {'C', 0} , {'D', 1000}, {'H', 2000}, {'S', 3000} };

struct Card {
	char value, suit;
	int priority;
	Card() {}
	Card(char v, char s) : value(v), suit(s) { priority = v_pri[v] + s_pri[s]; }
	bool operator < (const Card& a) { return priority < a.priority; }
};

class Convert {
public:
	string ToString(const Card& card) {
		string ans = "";
		if (v_pri[card.value] <= 10) ans += to_string(v_pri[card.value]);
		else if (card.value == 'J') ans += "Jack";
		else if (card.value == 'Q') ans += "Queen";
		else if (card.value == 'K') ans += "King";
		else ans += "Ace";
		if (card.suit == 'C') ans += " of Clubs";
		else if (card.suit == 'D') ans += " of Diamonds";
		else if (card.suit == 'H') ans += " of Hearts";
		else ans += " of Spades";
		return ans;
	}
	Card ToCard(int x) {
		char s, v;
		if (x > 39) s = 'S';
		else if (x > 26) s = 'H';
		else if (x > 13) s = 'D';
		else s = 'C';
		x %= 13;
		if (!x) x = 13;
		if (x < 9) v = x + '1';
		if (x == 9) v = 'T';
		if (x == 10) v = 'J';
		if (x == 11) v = 'Q';
		if (x == 12) v = 'K';
		if (x == 13) v = 'A';
		return Card(v, s);
	}
};
Convert convert;

class Deck {
	Card cards[53];
	vector<int> shuffles[103];
public:
	Deck() {
		for (int i = 1; i < 53; i++) cards[i] = convert.ToCard(i);
	}
	void ReadShuffles(int n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < 53; j++) {
				int k;
				cin >> k;
				shuffles[i].push_back(k);
			}
		}
	}
	void Shuffle(int k) {
		Card temp[53];
		for (int i = 0; i < 52; i++) {
			int j = shuffles[k][i];
			temp[i + 1] = cards[j];
		}
		for (int i = 1; i < 53; i++) cards[i] = temp[i];
	}
	void Print() {
		for (int i = 1; i < 53; i++) cout << convert.ToString(cards[i]) << "\n";
	}
};

void Process() {
	if (ct) cout << "\n";
	ct = 1;
	int n, k;
	cin >> n;
	Deck deck;
	deck.ReadShuffles(n);
	cin.ignore();
	string s;
	while (getline(cin, s)) {
		try { k = stoi(s); }
		catch (exception ex) { break; }
		deck.Shuffle(k);
	}
	deck.Print();
}

int main() {
	FASTIO();

	ct = 0;
	int T = 1;
	cin >> T;
	while (T--) Process();
	return 0;
}


/*
void DEBUG() {
	cout << "DEBUG" << ":\n";

	cout << "END OF DEBUG\n";
}
//*/