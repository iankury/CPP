#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, r1, c1, r2, c2;
int side;

bool Read() {
  cin >> n;
  if (n == 0 || cin.eof())
    return 0;
  cin >> r1 >> c1 >> r2 >> c2;

  return 1;
}

char At(int i, int j) {
  int dist = abs(i - (n - 1)) + abs(j - (n - 1));
  if (dist >= n)
    return '.';
  return (dist % 26) + 'a';
}

void Process() {
  cout << "Case " << ++ct << ":\n";
  side = 2 * n - 1;
  for (int i = r1; i <= r2; i++) {
    for (int j = c1; j <= c2; j++)
      cout << At(i % side, j % side);
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}
