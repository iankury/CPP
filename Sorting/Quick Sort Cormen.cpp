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

void Swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int Partition(int *a, int p, int r) {
	int i = p - 1;
	for (int j = p; j < r - 1; j++) {
		if (a[j] <= a[r - 1]) {
			i++;
			Swap(a[i], a[j]);
		}
	}
	Swap(a[i + 1], a[r - 1]);
	return i + 1;
}

void Quicksort(int *a, int p, int r) {
	if (p >= r) return;
	int q = Partition(a, p, r);
	Quicksort(a, p, q);
	Quicksort(a, q + 1, r);
}

void Process() {
	int n, a[N];
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	Quicksort(a, 0, n);
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}