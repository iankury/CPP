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

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;

struct Pinha {
  int x, fx;
  Pinha() {}
  Pinha(int _x) : x(_x), fx(_x % m) {}
  bool operator < (const Pinha& p) const {
    if (fx == p.fx) {
      if (x % 2 && p.x % 2 == 0)
        return 1;
      if (x % 2 == 0 && p.x % 2)
        return 0;
      if (x % 2)
        return x > p.x;
      return x < p.x;
    }
    return fx < p.fx;
  }
};
Pinha a[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  if (!n && !m) {
    cout << "0 0\n";
    return 0;
  }
  int k;
  for (int i = 0; i < n; i++) {
    cin >> k;
    a[i] = Pinha(k);
  }

  return 1;
}

void Process() {
  sort(a, a + n);
  cout << n << " " << m << "\n";
  for (int i = 0; i < n; i++)
    cout << a[i].x << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}