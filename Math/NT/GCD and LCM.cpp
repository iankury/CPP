#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int GCD(int _a, int _b) { return _b ? GCD(_b, _a % _b) : _a; }

int LCM(int _a, int _b) { return _a * (_b / GCD(_a, _b)); }

ll GCD(ll _a, ll _b) { return _b ? GCD(_b, _a % _b) : _a; }

ll LCM(ll _a, ll _b) { return _a * (_b / GCD(_a, _b)); }

int main() {
	

	return 0;
}