#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 2005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Point {
  int r, c;
  bool operator != (const Point& p) const { 
    return r != p.r || c != p.c; 
  }
};
const Point NIL = { -1, -1 };

int ct = 0;
vector<Point> p1, p2;
vector<vi> a;
int n, m, p1_sz, p2_sz;
int dc[] = { 0, 1, 0, -1 }, dr[] = { 1, 0, -1, 0 };
Point pi[N][N];

bool In_Bounds(const Point& p) {
  return p.r >= 0 && p.r <= n && p.c >= 0 && p.c <= m;
}

int Path_Length(Point p) {
  int ans = 0;
  while (pi[p.r][p.c] != NIL) {
    ans++;
    p = pi[p.r][p.c];
  }
  return ans;
}

bool Read() {
  n = m = 0;
  p1.clear();
  p2.clear();
  
  cin >> p1_sz;
  if (!p1_sz) return 0;
  p1.resize(p1_sz);
  for (int i = 0; i < p1_sz; i++) {
    cin >> p1[i].r >> p1[i].c;
    n = max(n, p1[i].r);
    m = max(m, p1[i].c);
  }
  cin >> p2_sz;
  p2.resize(p2_sz);
  for (int i = 0; i < p2_sz; i++) {
    cin >> p2[i].r >> p2[i].c;
    n = max(n, p2[i].r);
    m = max(m, p2[i].c);
  }

  return 1;
}

void Process() {
  a.assign(n + 1, vi(m + 1, 0));
  queue<Point> Q;
  for (Point& p : p1) {
    a[p.r][p.c] = 1;
    pi[p.r][p.c] = NIL;
    Q.push(p);
  }
  for (Point& p : p2) {
    a[p.r][p.c] = 2;
    pi[p.r][p.c] = NIL;
    Q.push(p);
  }
  Point cur, neib;
  while (!Q.empty()) {
    cur = Q.front();
    Q.pop();
    for (int i = 0; i < 4; i++) {
      neib = { cur.r + dr[i], cur.c + dc[i] };
      if (In_Bounds(neib) && a[neib.r][neib.c] != a[cur.r][cur.c]) {
        if (a[neib.r][neib.c]) {
          cout << 1 + Path_Length(cur) + Path_Length(neib) << "\n";
          return;
        }
        else {
          pi[neib.r][neib.c] = cur;
          a[neib.r][neib.c] = a[cur.r][cur.c];
          Q.push(neib);
        }
      }
    }
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}