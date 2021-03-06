#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctype.h>
#include <sstream>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

struct Light {
	int green, red;
	Light(int cycle) {
		green = cycle - 5;
		red = cycle + 5;
	}
	bool Green(int time) {
		int x = (time % (green + red));
		return (x && x <= green);
	}
};

string Format_Time(int x) {
	string s, m, h;
	s = m = h = "00";
	int secs = x % 60;
	s[1] = (secs % 10) + '0';
	s[0] = (secs / 10) + '0';
	int min = (x / 60) % 60;
	m[1] = (min % 10) + '0';
	m[0] = (min / 10) + '0';
	int hours = x / 3600;
	h[1] = (hours % 10) + '0';
	h[0] = (hours / 10) + '0';
	return (h + ":" + m + ":" + s);
}

void Process() {
	int x;
	while (cin >> x, x) {
		int min = 999;
		bool green[18010];
		memset(green, 1, sizeof green);
		vector<Light> lights;
		do {
			lights.push_back(Light(x));
			if (x < min) min = x;
		} while (cin >> x, x);
		int k = min + 1;
		bool virgin;
		for (auto& y : lights) {
			virgin = 1;
			for (int i = k; i < 18002; i++) {
				if (green[i]) {
					if (y.Green(i)) {
						if (virgin) {
							k = i;
							virgin = 0;
						}
					}
					else green[i] = 0;
				}
			}
		}
		if (virgin) cout << "Signals fail to synchronise in 5 hours\n";
		else cout << Format_Time(k - 1) << "\n";
	}
	int trash;
	cin >> x >> trash;
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}