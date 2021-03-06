#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 15;

void Merge(int *a, int l, int r, int mid) {
	int i = l, j = mid + 1, k = l, b[N];
	while (i <= mid && j <= r) {
		int &x = a[i] < a[j] ? i : j;
		b[k] = a[x];
		x++;
		k++;
	}
	for (; i <= mid; i++, k++) b[k] = a[i];
	for (; j <= r; j++, k++) b[k] = a[j];
	for (int i = l; i <= r; i++) a[i] = b[i];
}

void MergeSort(int* a, int l, int r) {
	if (l >= r) return;
	int mid = l + (r - l) / 2;
	MergeSort(a, l, mid);
	MergeSort(a, mid + 1, r);
	Merge(a, l, r, mid);
}

void Process() {
	int a[N], n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	MergeSort(a, 0, n - 1);
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


/*
void DEBUG() {
	cout << "DEBUG" << ":\n";

	cout << "END OF DEBUG\n";
}
//*/