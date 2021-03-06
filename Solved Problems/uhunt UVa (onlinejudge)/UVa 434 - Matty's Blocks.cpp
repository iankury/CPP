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

const int N = 8, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a[N], b[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  return 1;
}

void Process() {
  int p = 0, q = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) q += min(a[i], b[j]);
  for (int i = 0; i < n; i++) {
    int j = 0;
    for (; j < n; j++) {
      if (a[i] == b[j]) {
        p += a[i];
        b[j] = 0;
        break;
      }
    }
    if (j == n) p += a[i];
  }
  for (int j = 0; j < n; j++) if (b[j]) p += b[j];
    
  cout << "Matty needs at least " << p << " blocks, and can add at most " << q - p << " extra blocks.\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}