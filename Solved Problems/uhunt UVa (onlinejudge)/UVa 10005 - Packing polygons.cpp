#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const double PI = 3.14159265358979323846, EPS = 0.0000000001;

struct Point_ll {
  ll x, y;
  Point_ll() {}
  Point_ll(ll x, ll y) : x(x), y(y) {}
};
bool operator == (const Point_ll& p1, const Point_ll& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}
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
  Line() {}
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
  Vec() {}
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

struct Circle {
  double radius, area, circumference;
  Point possible_center1, possible_center2;
  Circle(double radius) : radius(radius) {}
  void Init() {
    area = PI * radius * radius;
    circumference = 2. * PI * radius;
  }
  bool Get_Center(const Point& p1, const Point& p2) {
    double dSq = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    double det = radius * radius / dSq - 0.25;
    if (det < 0.) 
      return 0;
    double h = sqrt(det);
    possible_center1.x = (p1.x + p2.x) * .5 + (p1.y - p2.y) * h;
    possible_center1.y = (p1.y + p2.y) * .5 + (p2.x - p1.x) * h;
    possible_center2.x = (p1.x + p2.x) * .5 + (p2.y - p1.y) * h;
    possible_center2.y = (p1.y + p2.y) * .5 + (p1.x - p2.x) * h;
    return 1;
  }
};

struct Triangle {
  Point p1, p2, p3;
  double area, s1, s2, s3, semip;
  void Init() {
    semip = (s1 + s2 + s3) / 2;
    area = sqrt(semip * (semip - s1) * (semip - s2) * (semip - s3));
  }
  Triangle(double s1, double s2, double s3)
    : s1(s1), s2(s2), s3(s3) {
    Init();
  }
  Triangle(const Point& p1, const Point& p2, const Point& p3)
    : p1(p1), p2(p2), p3(p3) {
    s1 = Euclidean_Distance(p1, p2);
    s2 = Euclidean_Distance(p2, p3);
    s3 = Euclidean_Distance(p1, p3);
    Init();
  }
  double Incircle_Radius() { return area / semip; }
  double Circumcircle_Radius() { return s1 * s2 * s3 / (4. * area); }
  Point Circumcircle_Center() {
    Point ans;
    Point mid1 = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    Point mid2 = Point((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
    Line per1 = Perpendicular_Line(Line(p1, p2), mid1);
    Line per2 = Perpendicular_Line(Line(p2, p3), mid2);
    return Intersection(per1, per2);
  }
  Point Incircle_Center() {
    double ratio = s1 / s3;
    Point p = Translate(p2, Vec(p2, p3).Scale(ratio / (1 + ratio)));
    ratio = s1 / s2;
    p = Translate(p1, Vec(p1, p3).Scale(ratio / (1 + ratio)));
    return Intersection(Line(p1, p), Line(p2, p));
  }
};

struct Rectangle {
  Point_ll bottom_left, top_right;
  Rectangle() {}
  Rectangle(const Point_ll& bottom_left, const Point_ll& top_right)
    : bottom_left(bottom_left), top_right(top_right) {}
  operator bool() { // Proper 2D rectangle
    return bottom_left.x < top_right.x&& bottom_left.y < top_right.y;
  }
};
bool operator == (const Rectangle& r1, const Rectangle& r2) {
  return r1.bottom_left == r2.bottom_left && r1.top_right == r2.top_right;
}
istream& operator >> (istream& is, Rectangle& _a) {
  is >> _a.bottom_left >> _a.top_right;
  return is;
}
ostream& operator << (ostream& os, Rectangle& _a) {
  os << _a.bottom_left << " " << _a.top_right;
  return os;
}

Rectangle Intersection(const Rectangle& r1, const Rectangle& r2) {
  return Rectangle(
    { max(r1.bottom_left.x, r2.bottom_left.x),
      max(r1.bottom_left.y, r2.bottom_left.y) },
    { min(r1.top_right.x, r2.top_right.x),
      min(r1.top_right.y, r2.top_right.y) });
}

int n;
vector<Point> p;
double r;

bool Read() {
  cin >> n;
  if (n == 0 || cin.eof())
    return 0;
  p.resize(n);
  for (int i = 0; i < n; i++)
    cin >> p[i];
  cin >> r;

  return 1;
}

void Process() {
  bool win;
  double d;
  Circle a(r);
  for (int i = 0; i < n - 1; i++)
    for (int j = i + 1; j < n; j++) {
      d = Euclidean_Distance(p[i], p[j]);
      if (d > 2. * r) {
        cout << "There is no way of packing that polygon.\n";
        return;
      }
      if (fabs(d - 2. * r) < EPS) {
        Point mid((p[i].x + p[j].x) / 2., (p[i].y + p[j].y) / 2.);
        win = 1;
        for (int k = 0; k < n; k++)
          if (k != i && k != j)
            if (Euclidean_Distance(p[k], mid) > r) {
              win = 0;
              break;
            }
        if (win) {
          cout << "The polygon can be packed in the circle.\n";
          return;
        }
      }
      else {
        if (!a.Get_Center(p[i], p[j]))
          continue;
        win = 1;
        for (int k = 0; k < n; k++)
          if (k != i && k != j)
            if (min(Euclidean_Distance(a.possible_center1, p[k]),
              Euclidean_Distance(a.possible_center2, p[k])) > r) {
              win = 0;
              break;
            }
        if (win) {
          cout << "The polygon can be packed in the circle.\n";
          return;
        }
      }
    }
  cout << "There is no way of packing that polygon.\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}