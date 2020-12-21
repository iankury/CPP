#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

const double PI = 3.14159265359, EPS = 0.000000001;

struct Point { double x, y; };
istream& operator >> (istream& is, Point& _a) { is >> _a.x >> _a.y; return is; }
ostream& operator << (ostream& os, Point& _a) { os << _a.x << " " << _a.y; return os; }

double Euclidean_Distance(const Point& _a, const Point& _b) {
  return hypot(_a.x - _b.x, _a.y - _b.y);
}

struct Line { // ax + by + c = 0
  double a, b, c; 
  Line(double a, double b, double c) : a(a), b(b), c(c) {}
  Line(const Point& _a, const Point& _b) {
    if (fabs(_a.x - _b.x) < EPS) {
      a = 1;
      b = 0;
      c = -_a.x;
    }
    else {
      a = -(_a.y - _b.y) / (_a.x - _b.x);
      b = 1.;
      c = -(a * _a.x) - _a.y;
    }
  }
}; 

Point Intersection(const Line& _a, const Line& _b) {
  Point ans;
  ans.x = (_b.b * _a.c - _a.b * _b.c) / (_b.a * _a.b - _a.a * _b.b);
  ans.y = fabs(_a.b) > EPS ? -(_a.a * ans.x + _a.c) : -(_b.a * ans.x + _b.c);
  return ans;
}

int n;
vector<Point> a;

bool Read() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  sort(begin(a), end(a), [](const Point& _a, const Point& _b) {
    return _a.x < _b.x; });
  vector<double> mx(n);
  mx[n - 1] = a[n - 1].y;
  for (int i = n - 2; i >= 0; i--) 
    mx[i] = max(mx[i + 1], a[i].y);
  int st = a[0].y > a[1].y ? 1 : 2;
  double ans = 0;
  for (int i = st; i < n; i += 2) {
    if (mx[i - 1] < mx[i] + EPS)
      continue;
    Line hor(0, 1, -mx[i]);
    Line mountain(a[i - 1], a[i]);
    Point intersection = Intersection(hor, mountain);
    ans += Euclidean_Distance(a[i - 1], intersection);
  }
  cout << fixed << setprecision(2) << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}