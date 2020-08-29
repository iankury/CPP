#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
int a[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  cin >> m;

  return 1;
}

void Process() {
  int si = 0, sj = 0;
  int bestdif = BIG;
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    int key = m - a[i];
    if (key < a[i])
      break;
    if (key == a[i]) {
      if ((i == 0 || a[i - 1] != a[i]) && (i == n - 1 || a[i + 1] != a[i]))
        continue;
    }
    if (binary_search(a, a + n, key)) {
      if (key - a[i] < bestdif) {
        bestdif = key - a[i];
        si = a[i];
        sj = key;
      }
    }
  }
  cout << "Peter should buy books whose prices are " << si << " and " << sj << ".\n\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}