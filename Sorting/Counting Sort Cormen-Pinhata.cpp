#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007;

void Counting_Sort(int* a, int st, int n, int k) {
	int freq[N];
	memset(freq, 0, sizeof freq);
	for (int i = st; i <= n; i++) freq[a[i]]++;
	int j = st;
	for (int i = 0; i <= k; i++) {
		while (freq[i]) {
			a[j] = i;
			j++;
			freq[i]--;
		}
	}
}

void Process() {
	int n, k, a[N];
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	Counting_Sort(a, 1, n, k);
	for (int i = 1; i <= n; i++) cout << a[i] << " ";
	cout << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}