#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
std::mt19937 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 100005, M = 1000000007;

void Swap(int& p, int& q) {
	int temp = p;
	p = q;
	q = temp;
}

int Randomized_Partition(int* a, int p, int r) {
	int luck = (rng() % (r + 1 - p)) + p;
	Swap(a[luck], a[r]);
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (a[j] <= a[r]) {
			i++;
			Swap(a[i], a[j]);
		}
	}
	Swap(a[r], a[i + 1]);
	return i + 1;
}

void Randomized_Quicksort(int* a, int p, int r) { // r inclusive
	if (p >= r) return;
	int q = Randomized_Partition(a, p, r);
	Randomized_Quicksort(a, p, q - 1);
	Randomized_Quicksort(a, q + 1, r);
}

void Process() {
	int n, a[N];
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	Randomized_Quicksort(a, 0, n - 1);
	for (int i = 0; i < n; i++) cout << a[i] << " ";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}