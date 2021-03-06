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
string To_Dollars(int cents) {
	bool minus = cents < 0 ? 1 : 0;
	if (minus) cents *= (-1);
	string ans = minus ? "-" : "";
	if (cents < 100) ans += "0.";
	else ans += (to_string(cents / 100) + ".");
	if ((cents % 100)< 10) ans += "0";
	ans += cents % 100 ? to_string(cents % 100) : "0";
	return ans;
}

struct Trans { string code; int cents; };

struct Acc {
	int order, cents;
	string code;
	vector<Trans> trans;
	void Compute() { for (auto& x : trans) cents += x.cents; cents *= (-1); }
};

void Process() {
	map<string, string> dic;
	map<string, Acc> acc;
	vector<Acc*> ans;
	string s;
	while (getline(cin, s), s.substr(0, 3) != "000") dic[s.substr(0, 3)] = s.substr(3);
	int k = 0;
	while (getline(cin, s), s.substr(0, 3) != "000") {
		string ind = s.substr(0, 3), cd = s.substr(3, 3);
		int cents = stoi(s.substr(6));
		auto itr = acc.find(ind);
		if (itr == acc.end()) acc[ind] = Acc{ k, 0, ind, vector<Trans>{ {cd, cents} } };
		else itr->second.trans.push_back({ cd, cents });
		k++;
	}
	for (auto& x : acc) {
		x.second.Compute();
		if (x.second.cents) ans.push_back(&x.second);
	}
	sort(ans.begin(), ans.end(), [](const Acc* p, const Acc* q) { return p->order < q->order; });
	for (auto& x : ans) {
		cout << "*** Transaction " << x->code << " is out of balance ***\n";
		for (auto& y : x->trans) {
			string valor = To_Dollars(y.cents), nome = dic[y.code];
			int espacos = 41 - valor.length() - nome.length();
			cout << y.code << " " << nome;
			for (int i = 0; i < espacos; i++) cout << " ";
			cout << To_Dollars(y.cents) << "\n";
		}
		string valor = To_Dollars(x->cents);
		int espacos = 27 - valor.length();
		cout << "999 Out of Balance";
		for (int i = 0; i < espacos; i++) cout << " ";
		cout << To_Dollars(x->cents) << "\n\n";
	}
}

int main() {
	FASTIO();
	int T = 1;
	//cin >> T;
	while (T--) Process();
	return 0;
}