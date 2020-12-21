#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

const double PI = 3.14159265359, EPS = 0.0000000001;

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
};
istream& operator >> (istream& is, Point& _a) { is >> _a.x >> _a.y; return is; }
ostream& operator << (ostream& os, Point& _a) { os << _a.x << " " << _a.y; return os; }

double Euclidean_Distance(const Point& _a, const Point& _b) {
  return hypot(_a.x - _b.x, _a.y - _b.y);
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

struct Pole {
  Point p;
  int z;
  double ang;
  void Get_Ang() {
    ang = Angle_CCW_From_X_Axis(p);
  }
  bool operator < (const Pole& _a) const {
    if (fabs(ang - _a.ang) < EPS)
      return Euclidean_Distance(p, { 0, 0 }) < Euclidean_Distance(_a.p, { 0, 0 });
    return ang < _a.ang;
  }
};
istream& operator >> (istream& is, Pole& _a) { is >> _a.p >> _a.z;  return is; }

int n, ct = 0;
vector<Pole> poles;

bool Read() {
  cin >> n;
  if (n == 0 || cin.eof())
    return 0;
  poles.resize(n);
  for (int i = 0; i < n; i++)
    cin >> poles[i];

  return 1;
}

void Process() {
  cout << "Data set " << ++ct << ":\n";
  for (int i = 0; i < n; i++)
    poles[i].Get_Ang();
  sort(begin(poles), end(poles));
  int mx = -1;
  double last_ang = -88;
  vector<Pole> ans;
  for (int i = 0; i < n; i++) {
    if (fabs(poles[i].ang - last_ang) < EPS) {
      if (poles[i].z <= mx)
        ans.push_back(poles[i]);
      mx = max(mx, poles[i].z);
    }
    else 
      mx = poles[i].z;
    last_ang = poles[i].ang;
  }
  if (ans.empty())
    cout << "All the lights are visible.\n";
  else {
    cout << "Some lights are not visible:\n";
    sort(begin(ans), end(ans), [](const Pole& p1, const Pole& p2) {
      if (p1.p.x == p2.p.x)
        return p1.p.y < p2.p.y;
      return p1.p.x < p2.p.x;
      });
    for (int i = 0; i < ans.size() - 1; i++)
      cout << "x = " << ans[i].p.x << ", y = " << ans[i].p.y << ";\n";
    cout << "x = " << ans.back().p.x << ", y = " << ans.back().p.y << ".\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}