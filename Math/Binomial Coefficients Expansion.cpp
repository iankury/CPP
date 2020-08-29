#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
string s, v1, v2;

/*
SAMPLE INPUT:
3
(a+b)^1
(alpha+omega)^2
(acm+icpc)^3
*/

const int DPSIZE = 32; // For bigger must use BIGINT

ll C[DPSIZE][DPSIZE];

void Build_C() {
  for (int i = 0; i < DPSIZE; i++)
    C[i][0] = C[i][i] = 1;
  for (int i = 2; i < DPSIZE; i++)
    for (int j = 1; j < i; j++)
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
}

bool Read() {
  cin >> s;

  return 1;
}

void Print_One(int c, int x1, int x2) {
  string sx1, sx2;
  if (x1 > 1)
    sx1 = "^" + to_string(x1);
  if (x2 > 1)
    sx2 = "^" + to_string(x2);
  if (c > 1)
    cout << c << '*';
  if (x1 && x2)
    cout << v1 << sx1 << '*' << v2 << sx2;
  else if (x2)
    cout << v2 << sx2;
  else
    cout << v1 << sx1;
}

void Process() {
  cout << "Case " << ++ct << ": ";
  int idx = s.find_first_of('+'), idx2 = s.find_first_of(')');
  v1 = s.substr(1, idx - 1);
  v2 = s.substr(idx + 1, idx2 - idx - 1);
  int xp = stoi(s.substr(idx2 + 2));
  for (int i = 0; i <= xp; i++) {
    if (i)
      cout << '+';
    Print_One(C[xp][i], xp - i, i);
  }
  cout << "\n";
}

int main() {
  FASTIO();

  Build_C();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}