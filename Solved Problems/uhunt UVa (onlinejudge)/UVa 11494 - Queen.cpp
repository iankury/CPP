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

struct Point {
	int x, y;
	bool operator == (const Point& p) { return (x == p.x && y == p.y); }
};

struct Line {
	int m, b, C;
	char verhor;
	Line(const Point& p, char vh) : verhor(vh) {
		if (vh == 'v') C = p.x;
		else if (vh == 'h') C = p.y;
		else if (vh == 's') {
			m = 1;
			b = p.y - p.x;
		}
		else if (vh == 'd') {
			m = -1;
			b = p.y + p.x;
		}
		else cout << "Error, invalid vh char\n";
	}
	bool Contains(const Point& p) {
		if (verhor == 'v') return p.x == C;
		else if (verhor == 'h') return p.y == C;
		else return m * p.x + b == p.y;
	}
};

void Process() {
	Point p1, p2;
	while (cin >> p1.x >> p1.y >> p2.x >> p2.y, p2.y) {
		if (p1 == p2) cout << "0\n";
		else {
			Line v(p1, 'v'), h(p1, 'h'), s(p1, 's'), d(p1, 'd');
			if (v.Contains(p2) || h.Contains(p2) || s.Contains(p2) || d.Contains(p2))
				cout << "1\n";
			else cout << "2\n";
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