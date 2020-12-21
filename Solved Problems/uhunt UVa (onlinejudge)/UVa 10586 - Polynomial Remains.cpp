#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 10005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, k;
int a[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> k;
  if (n == -1 && k == -1)
    return 0;
  for (int i = 0; i <= n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  if (k == 0) {
    cout << "0\n";
    return;
  }
  int largest = n;
  while (1) {
    while (largest >= 0 && a[largest] == 0)
      largest--;
    if (largest < k)
      break;
    a[largest - k] -= a[largest];
    a[largest] = 0;
  }
  cout << a[0];
  for (int i = 1; i <= largest; i++)
    cout << " " << a[i];
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}