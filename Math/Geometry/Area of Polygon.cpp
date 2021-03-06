#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

struct Point { double x, y; };

double Cross_Product(Point a, Point b) { return a.x * b.y - a.y * b.x; }

double Area_Of_Polygon(Point* vertices, int n) { // n = number of vertices
	double sum = 0.0;
	for (int i = 0; i < n; i++) sum += Cross_Product(vertices[i], vertices[(i + 1) % n]);
	return abs(sum) / 2.0;
}

int main() {

	return 0;
}

/* DEBUG

*/