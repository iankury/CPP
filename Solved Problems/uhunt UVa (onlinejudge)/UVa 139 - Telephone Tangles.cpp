#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <iterator>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

struct Place {
	string name;
	int price;
};

struct Call {
	Place place;
	string code, phone;
	int minutes;
	int Spent() { return minutes * place.price; }
};

map<string, Place> codes;

vector<Call> calls;

string Format_Dollars(int cents) {
	int dollars = cents / 100;
	string s = to_string(dollars);
	cents %= 100;
	string extra = cents < 10 ? "0" : "";
	if (cents) s += ("." + extra + to_string(cents));
	else s += ".00";
	return s;
}

void Print(const string& a, const string& b, const string& c,
	const string& d, const string& e, const string& f) {
	cout << left << setw(16) << a << setw(25) << b << right << setw(10) << c <<
		setw(5) << d << setw(6) << e << setw(7) << f << "\n";
}

void Process() {
	string s, t;
	while (cin >> s, s != "000000") {
		cin.ignore();
		getline(cin, t);
		int ind = t.find_first_of('$');
		codes[s] = { t.substr(0, ind), stoi(t.substr(ind + 1)) };
	}
	while (cin >> s, s != "#") {
		cin >> t;
		calls.push_back({ {"", 0}, "", "", stoi(t) });
		int k = calls.size() - 1;
		if (s[0] != '0') {
			calls[k].place = { "Local", 0 };
			calls[k].phone = s;
		}
		else {
			string x = "";
			bool found = 0;
			for (int i = 0; !found && i < s.length(); i++) {
				x.push_back(s[i]);
				if (codes.count(x)) {
					int l = s.length() - x.length();
					if ((x[1] == '0' && (l < 4 || l > 10)) || (x[1] != '0' && (l < 4 || l > 7))) continue;
					calls[k].place = codes[x];
					calls[k].code = x;
					calls[k].phone = s.substr(i + 1);
					found = 1;
				}
			}
			if (!found) {
				calls[k].place = { "Unknown", 0 };
				calls[k].code = "";
				calls[k].phone = s;
			}
		}
	}
	for (auto call : calls) {
		if (call.place.name == "Unknown") {
			Print((call.code + call.phone), call.place.name, "",
				to_string(call.minutes), "", "-1.00");
		}
		else {
			Print((call.code + call.phone), call.place.name,
				call.phone, to_string(call.minutes),
				Format_Dollars(call.place.price),
				Format_Dollars(call.Spent()));
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