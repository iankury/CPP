#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

int Pow(int n, int p){
	if (!p) return 1;
	int ans = 1;
	while (p--) ans *= n;
	return ans;
}

int Process() {
	string guess;
	int R, W, r, w;
	cin >> guess >> R >> W;
	int n = guess.length();
	if (R == n) return 1;
	int freq[11]{ 0 };
	for (int i = 0; i < n; i++) freq[guess[i] - '0']++;
	int distinct_elements = 0;
	for (int i = 1; i < 10; i++)
		if (freq[i]) distinct_elements++;
	if (!R && !W) return Pow(9 - distinct_elements, n);
	int start = 1, addon = 10, ans = 0;
	for (int i = 1; i < n; i++) {
		start += addon;
		addon *= 10;
	}
	int end = start * 9;
	for (int i = start; i <= end; i++) {
		memset(freq, 0, sizeof freq);
		int mayRepeat[11]{ 0 };
		string code = to_string(i);
		for (int i = 0; i < n; i++) freq[code[i] - '0']++;
		if (freq[0]) continue;
		int r = 0, w = 0;
		for (int j = 0; j < n; j++) {
			if (guess[j] == code[j]) {
				r++;
				freq[guess[j] - '0']--;
				mayRepeat[guess[j] - '0']++;
			}
		}
		if (R != r) continue;
		for (int j = 0; j < n && w < W; j++) {
			if (guess[j] != code[j] && freq[guess[j] - '0']) {
				w++;
				freq[guess[j] - '0']--;
				mayRepeat[guess[j] - '0']++;
			}
		}
		bool fail = 0;
		for (int j = 0; j < n; j++) {
			if (freq[guess[j] - '0']) {
				if (!mayRepeat[guess[j] - '0']) fail = 1;
				mayRepeat[guess[j] - '0']--;
			}
		}
		if (!fail && W == w) ans++;
	}
	return ans;
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) cout << Process() << "\n";

	return 0;
}