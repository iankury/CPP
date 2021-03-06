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

const int N = 11, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
char a[N][N], b[N][N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> a[i][j];
    for (int j = 0; j < n; j++) cin >> b[i][j];
  }

  return 1;
}

bool Equal() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != b[i][j]) return 0;
  return 1;
}

bool R90() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != b[j][n - 1 - i]) return 0;
  return 1;
}

bool R180() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != b[n - 1 - i][n - 1  - j]) return 0;
  return 1;
}

bool R270() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != b[n - 1 - j][i]) return 0;
  return 1;
}

void Swap(char& p, char& q) {
  char temp = p;
  p = q;
  q = temp;
}

void Reflect() {
  for (int j = 0; j < n; j++) {
    int p = 0, q = n - 1;
    while (p < q) {
      Swap(a[p][j], a[q][j]);
      p++; q--;
    }
  }
}

void Process() {
  cout << "Pattern " << ++ct << " ";
  if (Equal()) cout << "was preserved.\n";
  else if (R90()) cout << "was rotated 90 degrees.\n";
  else if (R180()) cout << "was rotated 180 degrees.\n";
  else if (R270()) cout << "was rotated 270 degrees.\n";
  else {
    Reflect();
    if (Equal()) cout << "was reflected vertically.\n";
    else if (R90()) cout << "was reflected vertically and rotated 90 degrees.\n";
    else if (R180()) cout << "was reflected vertically and rotated 180 degrees.\n";
    else if (R270()) cout << "was reflected vertically and rotated 270 degrees.\n";
    else cout << "was improperly transformed.\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}