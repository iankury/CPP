#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 6, M = 1000000007;

class Queue {
	int a[N], head, tail;
public:
	Queue() : head(0), tail(0) {}
	bool Empty() { return head == tail; }
	bool Full() { return ((head == tail + 1) || (!head && tail == N - 1)); }
	void Enqueue(int x) {
		if (Full()) cout << "Error: Queue overflow.\n";
		else {
			a[tail] = x;
			if (tail == N - 1) tail = 0;
			else tail++;
		}
	}
	int Pop() {
		if (Empty()) cout << "Error: Queue underflow.\n";
		else {
			int x = a[head];
			if (head == N - 1) head = 0;
			else head++;
			cout << x << " popped.\n";
			return x;
		}
		return -1;
	}
	void Print_Pinhata() {
		for (int i = 0; i < N; i++) {
			if (i == head && i != tail) cout << "(( ";
			if (Empty() || (head < tail && (i < head || i >= tail))
				|| (head > tail && (i < head && i >= tail))) 
				cout << "a[" << i << "]: X ";
			else cout << "a[" << i << "]: " << a[i] << " ";
			if (!Empty() && (i == tail - 1 || (i == N - 1 && !tail))) 
				cout << ")) ";
		}
		cout << "\n";
	}
};

void Process() {
	Queue Q;
	while (1) {
		int x;
		cin >> x;
		if (x == 1) {
			int y;
			cin >> y;
			Q.Enqueue(y);
		}
		else if (x == 2) Q.Pop();
		else if (x == 3) {
			if (Q.Empty()) cout << "Queue is empty.\n";
			else cout << "Queue is not empty.\n";
		}
		else if (x == 4) {
			if (Q.Full()) cout << "Queue is full.\n";
			else cout << "Queue is not full.\n";
		}
		else Q.Print_Pinhata();
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}