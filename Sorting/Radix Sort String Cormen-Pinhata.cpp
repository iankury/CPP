#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int DIGITS = 4, K = 43;

int Char_At(const string& s, const int& position) {
	return (int)toupper(s[DIGITS - 1 - position]) - 48;
}

vector<string> Ct_Sort_By_Char(const vector<string>& a, const int& position) {
	int freq[K]{ 0 }, n = a.size();
	for (int i = 0; i < n; i++) freq[Char_At(a[i], position)]++;
	for (int i = 1; i < K; i++) freq[i] += freq[i - 1];
	vector<string> b;
	b.resize(n);
	for (int i = n - 1; i >= 0; i--) {
		b[-1 + freq[Char_At(a[i], position)]] = a[i];
		freq[Char_At(a[i], position)]--;
	}
	return b;
}

vector<string> Radix_Sort(const vector<string>& a) {
	int n = a.size();
	vector<string> ans = a;
	for (int i = 0; i < DIGITS; i++) ans = Ct_Sort_By_Char(ans, i);
	return ans;
}

void Process() {
	int lineBreakCount = 1;
	vector<string> a;
	string s;
	cout << "Type in alphanumeric strings of 4 chars. EXIT to finish.\n";
	while (cin >> s, s != "EXIT") a.push_back(s);
	a = Radix_Sort(a);
	for (int i = 0; i < a.size(); i++, lineBreakCount++) {
		cout << a[i] << " ";
		if (lineBreakCount == 15) {
			lineBreakCount = 0;
			cout << "\n";
		}
	}
	cout << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}