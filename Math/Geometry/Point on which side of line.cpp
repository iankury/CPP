#include <iostream>
using namespace std;
void FASTIO() { ios_base::sync_with_stdio(false); cin.tie(NULL); }

//bool debug = 0;
const int SIZE = 101;
const int LEFT = -1, RIGHT = 1, ON_THE_LINE = 0;

struct Point {
	double x, y;
};

double Cross_Product(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

Point Subtract(Point a, Point b) {
	Point result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

int Get_Direction(Point p, Point a, Point b) {
	// First translate Cartesian plane so that point a is on the origin:
	b = Subtract(b, a);
	p = Subtract(p, a);
	double cProd = Cross_Product(b, p);
	if (cProd > 0) return LEFT;
	else if (cProd < 0) return RIGHT;
	else return ON_THE_LINE;
} // Returns direction of point p in relation to line segment that goes from a to b.

int main() {
	FASTIO();



	return 0;
}

/* DEBUG

*/