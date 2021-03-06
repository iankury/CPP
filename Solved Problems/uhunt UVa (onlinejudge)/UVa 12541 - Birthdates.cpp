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
int n;

struct Date {
  int d, m, y;
  bool operator < (const Date& p) const {
    if (y == p.y) {
      if (m == p.m)
        return d < p.d;
      return m < p.m;
    }
    return y < p.y;
  }
};
Date old, young;
string little, big;

int main() {
  FASTIO();

  cin >> n;
  int d, m, y;
  string s;
  cin >> s >> d >> m >> y;
  little = big = s;
  old = young = { d, m, y };
  for (int i = 1; i < n; i++) {
    cin >> s >> d >> m >> y; 
    Date cur = { d, m, y };
    if (cur < old) {
      big = s;
      old = cur;
    }
    else if (young < cur) {
      little = s;
      young = cur;
    }
  }
  cout << little << "\n" << big << "\n";

  return 0;
}