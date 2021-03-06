#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;
int ct;

string Format_Dollars(double d) {
	ostringstream sstream;
	sstream << fixed;
	sstream << setprecision(2);
	sstream << d;
	string ans, s = sstream.str();
	int digits = s.length() - 3;
	int commas = digits % 3 ? digits / 3 : digits / 3 - 1;
	ans.resize(s.length() + commas + 1);
	ans[0] = '$';
	for (int i = 1; i < 4; i++) ans[ans.length() - i] = s[s.length() - i];
	for (int i = s.length() - 4, j = ans.length() - 4, k = 0; j && i >= 0; k++, j--, i--) {
		ans[j] = s[i];
		if (k == 2 && j > 1) {
			k = 0;
			j--;
			ans[j] = ',';
		}
	}
	return ans;
}

void Process() {
	double d, ans = 0;
	for (int i = 0; i < 12; i++) {
		cin >> d;
		ans += d;
	}
	ans /= 12;
	cout << ct << " " << Format_Dollars(ans) << "\n";
	ct++;
}

int main() {
	FASTIO();

	ct = 1;
	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}