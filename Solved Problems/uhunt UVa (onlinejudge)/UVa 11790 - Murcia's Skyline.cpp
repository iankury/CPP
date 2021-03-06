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

const int N = 500005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, h[N], w[N], LIS[N], LDS[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++) cin >> h[i];
  for (int i = 0; i < n; i++) cin >> w[i];

  return 1;
}

void Process() {
  cout << "Case " << ++ct << ". ";
  int lis, lds;
  lis = lds = LIS[0] = LDS[0] = w[0];
  for (int i = 1; i < n; i++) {
    LIS[i] = LDS[i] = w[i];
    for (int j = 0; j < i; j++) {
      if (h[i] < h[j] && LDS[j] + w[i] > LDS[i]) LDS[i] = LDS[j] + w[i];
      else if (h[i] > h[j] && LIS[j] + w[i] > LIS[i]) LIS[i] = LIS[j] + w[i];
    }
    if (LIS[i] > lis) lis = LIS[i];
    if (LDS[i] > lds) lds = LDS[i];
  }
  if (lds > lis) cout << "Decreasing (" << lds << "). Increasing (" << lis << ").\n";
  else cout << "Increasing (" << lis << "). Decreasing (" << lds << ").\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}