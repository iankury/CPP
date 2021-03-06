#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int wall_damage, m, n, bumpers;
ll sum;
enum { RIGHT, UP, LEFT, DOWN };
struct Point { 
	int row, col; 
	bool operator < (const Point& p) const { return row * m + col < p.row * m + p.col; }
};

struct Bumper { int reward, damage; };
Bumper* WALL;

map<Point, Bumper*> tiles;

class Ball {
	Point pos;
	int dir, life;
public:
	int score;
	Ball(int x, int y, int d, int hp) : pos(Point{ y, x }), dir(d), life(hp), score(0) {}
	void Rotate() {
		if (dir == RIGHT) dir = DOWN;
		else if (dir == DOWN) dir = LEFT;
		else if (dir == LEFT) dir = UP;
		else dir = RIGHT;
	}
	bool Bump(Bumper* bumper) {
		life -= bumper->damage;
		score += bumper->reward;
		Rotate();
		return life > 0;
	}
	bool Roll() {
		life--;
		if (life < 1) return 0;
		Point destiny = pos;
		if (dir == RIGHT) destiny.col++;
		else if (dir == DOWN) destiny.row--;
		else if (dir == LEFT) destiny.col--;
		else destiny.row++;
		Bumper* bumper = tiles[destiny];
		bool ans = 1;
		if (bumper) ans = Bump(bumper);
		else pos = destiny;
		return ans;
	}
};

void Build_Four_Walls() {
	WALL = new Bumper{ 0, wall_damage };
	for (int i = 1; i <= m; i++) tiles[Point{ 1, i }] = tiles[Point{ n, i }] = WALL;
	for (int i = 2; i < n; i++) tiles[Point{ i, 1 }] = tiles[Point{ i, m }] = WALL;
}

void Process() {
	cin >> m >> n >> wall_damage >> bumpers;
	Build_Four_Walls();
	for (int i = 0; i < bumpers; i++) {
		int x, y, value, cost;
		cin >> x >> y >> value >> cost;
		tiles[Point{ y, x }] = new Bumper{ value, cost };
	}
	int x, y, d, hp;
	sum = 0;
	while (cin >> x >> y >> d >> hp) {
		Ball ball(x, y, d, hp);
		while (ball.Roll()) {}
		cout << ball.score << "\n";
		sum += ball.score;
		cin.ignore();
		if (!isalnum(cin.peek()) || cin.eof()) break;
	}
	cout << sum << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}