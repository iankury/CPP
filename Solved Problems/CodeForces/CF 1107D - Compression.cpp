#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 5203, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
bool decode[4][255];
bool a[N][N];
int psa[N][N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  char c;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j += 4) {
      cin >> c;
      for (int k = 0; k < 4; k++)
        a[i][j + k] = decode[k][c];
    }

  return 1;
}

bool Valid(int x) {
  int sum;
  int key = x * x;
  for (int i = x - 1; i < n; i += x)
    for (int j = x - 1; j < n; j += x) {
      sum = psa[i][j];
      if (i - x >= 0) {
        sum -= psa[i - x][j];
        if (j - x >= 0) {
          sum -= psa[i][j - x];
          sum += psa[i - x][j - x];
        }
      }
      else if (j - x >= 0) 
        sum -= psa[i][j - x];
      if (sum != key && sum) 
        return 0;
    }
  return 1;
}

void Process() {
  memset(psa, 0, sizeof psa);
  psa[0][0] = a[0][0];
  for (int i = 1; i < n; i++)
    psa[0][i] = a[0][i] + psa[0][i - 1];
  for (int i = 1; i < n; i++)
    psa[i][0] = a[i][0] + psa[i - 1][0];
  for (int i = 1; i < n; i++)
    for (int j = 1; j < n; j++)
      psa[i][j] = a[i][j] + psa[i - 1][j] + psa[i][j - 1] - psa[i - 1][j - 1];
  vi div = { n };
  int d = 2;
  for (; d * d < n; d++)
    if (n % d == 0) {
      div.push_back(d);
      div.push_back(n / d);
    }
  if (n % d == 0)
    div.push_back(d);
  sort(rbegin(div), rend(div));
  for (int x : div) 
    if (Valid(x)) {
      cout << x << "\n";
      return;
    }
  cout << "1\n";
}

int main() {
  FASTIO();

  char offset = '0';
  for (int i = 0; i < 16; i++) {
    if (i == 10)
      offset = 'A' - 10;
    for (int j = 3; j >= 0; j--)
      decode[3 - j][i + offset] = i & (1 << j);
  }
    
  while (Read())
    Process();

  return 0;
}