#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N], b[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];

  return 1;
}

void Process() {
  int i, j, fuel;
  cout << "Case " << ++ct << ": ";
  for (i = 1; i <= n; i++) {
    fuel = 0;
    for (j = 0; j < n; j++) {
      int cur = i + j;
      if (cur > n) cur -= n;
      fuel += a[cur] - b[cur];
      if (fuel < 0) {
        i += j;
        break;
      }
      if (j == n - 1) {
        cout << "Possible from station " << i << "\n";
        return;
      }
    }
  }
  cout << "Not possible\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}