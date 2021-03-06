#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 50005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, f, fr[N], fc[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m >> f;
  for (int i = 0; i < f; i++)
    cin >> fr[i] >> fc[i];

  return 1;
}

void Process() {
  double sumr = 0, sumc = 0;
  for (int i = 0; i < f; i++) {
    sumr += fr[i];
    sumc += fc[i];
  }
  int r = (sumr / f), c = (sumc / f);
  int ansr = 0, ansc = 0;
  ll minmd = 0x3f3f3f3f3f3f3f3f, md;
  for (int i = r - 50; i < r + 50; i++) 
    for (int j = c - 50; j < c + 50; j++) {
      if (i && i <= n && j && j <= m) {
        md = 0;
        for (int k = 0; k < f; k++) 
          md += abs(fr[k] - i) + abs(fc[k] - j);
        if (md < minmd) {
          minmd = md;
          ansr = i;
          ansc = j;
        }
      }
    }

  cout << "(Street: " << ansr << ", Avenue: " << ansc << ")\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}