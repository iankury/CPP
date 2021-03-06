#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 5, M = 1000000007;

class Stack {
	int a[N], top;
public:
	Stack() : top(0) {}
	bool Empty() { return !top; }
	void Push(int x) {
		if (top < N - 1) {
			top++;
			a[top] = x;
		}
		else cout << "Error: Stack overflow.\n";
	}
	int Pop() {
		if (top) {
			top--;
			return a[top + 1];
		}
		cout << "Error: Stack underflow.\n";
		return -1;
	}
};

void Process() {
	Stack S;
	while (1) {
		int x;
		cin >> x;
		if (x == 1) {
			int y;
			cin >> y;
			S.Push(y);
		}
		else if (x == 2) cout << S.Pop() << " popped.\n";
		else {
			if (S.Empty()) cout << "Stack is empty.\n";
			else cout << "Stack is not empty.\n";
		}
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}