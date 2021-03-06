#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int SIZE = 1;

struct Point { int x, y; };
struct Line {
	double dy, dx, x1, y1;
	Line(const Point &p1, const Point &p2) {
		x1 = p1.x; 
		y1 = p1.y;
		dy = p2.y - y1; 
		dx = p2.x - x1;
	}
	bool InLine(const Point &p) { 
		if (!dx) return p.x == x1;
		return p.y == (dy * p.x - dy * x1) / dx + y1;
	}
};

int main() {
	FASTIO();
	


	return 0;
}

/*
void DEBUG() {
	cout << "DEBUG:\n";
	cout << "END OF DEBUG\n";
}
//*/