#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N], b[N], ans[N];

bool Read() {
  cin >> n;
  if (!n || cin.eof()) return 0;
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

  return 1;
}

bool In_Bounds(int p) { return p >= 0 && p < n; }

void Process() {
  memset(ans, -1, sizeof ans);
  int idx = -1;
  for (int i = 0; i < n; i++) {
    idx = i + b[i];
    if (In_Bounds(idx)) ans[idx] = a[i];
    else {
      cout << "-1\n";
      return;
    }
  }
  for (int i = 0; i < n; i++)
    if (ans[i] == -1) {
      cout << "-1\n";
      return;
    }
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}