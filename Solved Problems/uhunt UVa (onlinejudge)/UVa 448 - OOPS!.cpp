#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

int To_Dec(char c) {
	return (c >= '0' && c <= '9') ? c - '0' : 10 + (c - 'A');
}

int To_Dec(const string& s) {
	int ans = 0, mul = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		ans += mul * To_Dec(s[i]);
		mul *= 16;
	}
	return ans;
}

struct Inst {
	int wagons;
	string name;
};

map <char, Inst> dic{
	{'0', {2, "ADD"}}, {'1', {2, "SUB"}},
	{'2', {2, "MUL"}},{'3', {2, "DIV"}},
	{'4', {2, "MOV"}},{'5', {1, "BREQ"}},
	{'6', {1, "BRLE"}},{'7', {1, "BRLS"}},
	{'8', {1, "BRGE"}},{'9', {1, "BRGR"}},
	{'A', {1, "BRNE"}},{'B', {1, "BR"}},
	{'C', {3, "AND"}},{'D', {3, "OR"}},
	{'E', {3, "XOR"}},{'F', {1, "NOT"}}
};

void Process() {
	string s = "", r;
	while (cin >> r, r.size()) {
		s += r;
		cin.ignore();
		if (!isalnum(cin.peek())) break;
	}
	string w[3];
	for (int i = 0; i < s.length(); i++) {
		Inst inst = dic[s[i]];
		for (int j = 0; j < inst.wagons; j++) {
			w[j] = s.substr(i + 1, 4);
			i += 4;
		}
		cout << inst.name << " ";
		for (int j = 0; j < inst.wagons; j++) {
			if (j) cout << ",";
			if (w[j][0] == '0') cout << "R" << To_Dec(w[j]);
			else if (w[j][0] >= '4' && w[j][0] <= '7') cout << "$" << To_Dec(w[j]) - 16384;
			else if (w[j][0] >= '8' && w[j][0] <= 'B') cout << "PC+" << To_Dec(w[j]) - 32768;
			else cout << To_Dec(w[j]) - 49152;
		}
		cout << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}