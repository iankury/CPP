#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

const double PI = 3.14159265359, EPS = 0.000000001;

struct Point_ll {
  ll x, y;
  Point_ll() {}
  Point_ll(ll x, ll y) : x(x), y(y) {}
};
istream& operator >> (istream& is, Point_ll& _a) { is >> _a.x >> _a.y; return is; }
ostream& operator << (ostream& os, Point_ll& _a) { os << _a.x << " " << _a.y; return os; }

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point Rotate(double theta) { // CCW wrt 0,0
    double rad = theta * PI / 180.;
    return { x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad) };
  }
};
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

Line Perpendicular_Line(const Line& _a, const Point& _p) {
  double sl = 1. / (_a.a / _a.b);
  double cc = _p.y - sl * _p.x;
  return Line(-sl, 1, -cc);
}

bool Parallel_Lines(const Line& _a, const Line& _b) {
  return (fabs(_a.a - _b.a) < EPS) && (fabs(_a.b - _b.b) < EPS);
}

bool operator == (const Line& _a, const Line& _b) {
  return Parallel_Lines(_a, _b) && (fabs(_a.c - _b.c) < EPS);
}

Point Intersection(const Line& _a, const Line& _b) {
  Point ans;
  ans.x = (_b.b * _a.c - _a.b * _b.c) / (_b.a * _a.b - _a.a * _b.b);
  ans.y = fabs(_a.b) > EPS ? -(_a.a * ans.x + _a.c) : -(_b.a * ans.x + _b.c);
  return ans;
}

struct Vec {
  double x, y;
  Vec(double x, double y) : x(x), y(y) {}
  Vec(const Point& _a, const Point& _b) : x(_b.x - _a.x), y(_b.y - _a.y) {}
  Vec Scale(double _s) const { return { x * _s, y * _s }; }
  double Squared_Norm() { return x * x + y * y; }
};
double operator * (const Vec& _a, const Vec& _b) { return _a.x * _b.x + _a.y * _b.y; }
double Cross_Product(const Vec& _a, const Vec& _b) { return _a.x * _b.y - _a.y * _b.x; }

Point Translate(const Point& _p, const Vec& _v) { return { _p.x + _v.x, _p.y + _v.y }; }

Point Closest_Point_In_Line(const Point& _p, const Point& _a, const Point& _b) {
  Vec ap(_a, _p), ab(_a, _b);
  double u = ap * ab / ab.Squared_Norm();
  return Translate(_a, ab.Scale(u));
}

double Distance_To_Line(const Point& _p, const Point& _a, const Point& _b) {
  return Euclidean_Distance(_p, Closest_Point_In_Line(_p, _a, _b));
}

Point Closest_Point_In_Line_Segment(const Point& _p, const Point& _a, const Point& _b) {
  Vec ap(_a, _p), ab(_a, _b);
  double u = ap * ab / ab.Squared_Norm();
  if (u < 0.0)
    return { _a.x, _a.y };
  if (u > 1.0)
    return { _b.x, _b.y };
  return Translate(_a, ab.Scale(u));
}

double Distance_To_Line_Segment(const Point& _p, const Point& _a, const Point& _b) {
  return Euclidean_Distance(_p, Closest_Point_In_Line_Segment(_p, _a, _b));
}

double Angle(const Point& _a, const Point& _o, const Point& _b) { // In RAD
  Vec oa(_o, _a), ob(_o, _b);
  return acos(oa * ob / sqrt(oa.Squared_Norm() * ob.Squared_Norm()));
}

double Angle_CCW_From_X_Axis(const Point& _a) {
  if (fabs(_a.x) < EPS) {
    if (fabs(_a.y) < EPS)
      return 0;
    if (_a.y > 0)
      return PI / 2.;
    return 3. * PI / 2.;
  }
  else if (fabs(_a.y) < EPS) {
    if (_a.x > 0)
      return 0;
    return PI;
  }
  double ans = atan(_a.y / _a.x);
  if (_a.y < 0)
    ans += PI;
  return ans;
}

bool Left_Of_Line(const Point& _p, const Point& _a, const Point& _b) {
  // CCW test: true if point _p is to the left of line
  return Cross_Product(Vec(_a, _b), Vec(_a, _p)) > 0;
}

bool Collinear(const Point& _p, const Point& _a, const Point& _b) {
  // True if point _p in on line
  return fabs(Cross_Product(Vec(_a, _b), Vec(_a, _p))) < EPS;
}

struct Triangle {
  Point p1, p2, p3;
  double area, s1, s2, s3;
  void Compute_Area() {
    double semip = (s1 + s2 + s3) / 2;
    area = sqrt(semip * (semip - s1) * (semip - s2) * (semip - s3));
  }
  Triangle(double s1, double s2, double s3)
    : s1(s1), s2(s2), s3(s3) {
    Compute_Area();
  }
  Triangle(const Point& p1, const Point& p2, const Point& p3)
    : p1(p1), p2(p2), p3(p3) {
    s1 = Euclidean_Distance(p1, p2);
    s2 = Euclidean_Distance(p2, p3);
    s3 = Euclidean_Distance(p1, p3);
    Compute_Area();
  }
  double Circumcircle_Radius() {
    return s1 * s2 * s3 / (4. * area);
  }
  Point Circumcircle_Center() {
    Point ans;
    Point mid1 = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    Point mid2 = Point((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
    Line per1 = Perpendicular_Line(Line(p1, p2), mid1);
    Line per2 = Perpendicular_Line(Line(p2, p3), mid2);
    return Intersection(per1, per2);
  }
};

int n, ct = 0;
Point a, b, c;

bool Read() {
  cin >> n;
  if (n == 0 || cin.eof())
    return 0;
  cin >> a >> b >> c;

  return 1;
}

void Process() {
  Triangle t(a, b, c);
  double diam = 2. * t.Circumcircle_Radius();
  Point center = t.Circumcircle_Center();
  Point p(a.x - center.x, a.y - center.y);
  double bb_top = p.y, bb_bot = p.y, bb_left = p.x, bb_right = p.x;
  double ang = 360. / n;
  for (int i = 0; i < n; i++) {
    p = p.Rotate(ang);
    bb_top = max(bb_top, p.y);
    bb_bot = min(bb_bot, p.y);
    bb_left = min(bb_left, p.x);
    bb_right = max(bb_right, p.x);
  }
  cout << "Polygon " << ++ct << ": ";
  cout << fixed << setprecision(3) << fabs((bb_top - bb_bot) * (bb_left - bb_right)) << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}