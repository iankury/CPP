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

void Swap(int& p, int& q) {
	int temp = p;
	p = q;
	q = temp;
}

void Max_Heapify(int* a, int i, int n) {
	int l, r, largest;
	while(1) {
		l = 2 * i;
		r = l + 1;
		largest = (l <= n && a[l] > a[i]) ? l : i;
		if (r <= n && a[r] > a[largest]) largest = r;
		if (i != largest) {
			Swap(a[i], a[largest]);
			i = largest;
		}
		else break;
	}
}

void Build_Max_Heap(int *a, int n) {
	for (int i = n / 2; i > 0; i--) Max_Heapify(a, i, n);
}

void Heapsort(int* a, int n) {
	Build_Max_Heap(a, n);
	while (n > 1) {
		Swap(a[1], a[n]);
		Max_Heapify(a, 1, --n);
	}
}

void Process() {
	int n, a[44];
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	Heapsort(a, n);
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