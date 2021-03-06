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

struct Node {
	double data;
	Node* next;
};

class List {
	Node* head, *tail;
	int sz;
public:
	List() : head(0), sz(0), tail(0) {}
	bool Empty() { return !((bool)sz); }
	void Push(double data) {
		sz++;
		Node* p = new Node;
		p->data = data;
		p->next = 0;
		if (tail) tail->next = p;
		else head = p;
		tail = p;
	}
	double Pop() {
		sz--;
		double ans = head->data;
		Node* p = head;
		head = head->next;
		delete p;
		return ans;
	}
};

void Swap(double& p, double& q) {
	double temp = p;
	p = q;
	q = temp;
}

void Insertion_Sort(double* a, int p, int r) {
	for (int i = p + 1; i <= r; i++) {
		double key = a[i];
		int j;
		for (j = i - 1; j >= p && a[j] > key; j--) a[j + 1] = a[j];
		a[j + 1] = key;
	}
}

void Bucket_Sort(double* a, int n) {
	List buckets[10];
	for (int i = 0; i < n; i++) buckets[(int)(a[i] * 10.0)].Push(a[i]);
	int st = 0, j = 0;
	for (int i = 0; i < 10; i++) {
		for (; !buckets[i].Empty(); j++) a[j] = buckets[i].Pop();
		Insertion_Sort(a, st, j - 1);
		st = j;
	}
}

void Process() {
	int n, lineBreakCount = 1;
	double a[N];
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	Bucket_Sort(a, n);
	cout << "Output:\n";
	for (int i = 0; i < n; i++, lineBreakCount++) {
		cout << a[i] << " ";
		if (lineBreakCount == 10) {
			lineBreakCount = 0;
			cout << "\n";
		}
	}
	cout << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}