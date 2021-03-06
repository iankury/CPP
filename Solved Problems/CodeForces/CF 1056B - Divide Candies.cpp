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

int n, m;
int C[1005];

void Process() {
	cin >> n >> m;
	n++;
	for (int i = 0; i < m; i++)
		C[i * i % m] += n / m + (i < n % m);
	C[0]--;
	ll ans = 0;
	for (int i = 1; i < m; ++i) 
		ans += (ll)C[i] * C[m - i];
	ans += (ll)C[0] * C[0];
	cout << ans;
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