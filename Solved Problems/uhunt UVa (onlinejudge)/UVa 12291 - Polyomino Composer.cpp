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

const int N = 15, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;
char a[N][N], b[N][N];

bool Read() {
  cin >> n >> m;
  if (!n) return 0;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (s.length() < n) 
      for (int j = 0; j < n; j++) a[i][j] = '.';
    else
      for (int j = 0; j < n; j++) a[i][j] = s[j];
  }
  for (int i = 0; i < m; i++) {
    cin >> s;
    if (s.length() < m)
      for (int j = 0; j < m; j++) b[i][j] = '.';
    else
      for (int j = 0; j < m; j++) b[i][j] = s[j];
  }

  return 1;
}

bool In_Bounds(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

void Process() {
  int offset_r, offset_c, offset_a_r, offset_a_c, offset_b_r, offset_b_c;
  bool breaker = 0;
  for (offset_b_r = 0; offset_b_r < m; offset_b_r++) {
    for (offset_b_c = 0; offset_b_c < m; offset_b_c++)
      if (b[offset_b_r][offset_b_c] == '*') {
        breaker = 1;
        break;
      }
    if (breaker) break;
  }
  for (int k = 0; k < 2; k++) {
    breaker = 0;
    for (offset_a_r = 0; offset_a_r < n; offset_a_r++) {
      for (offset_a_c = 0; offset_a_c < n; offset_a_c++)
        if (a[offset_a_r][offset_a_c] == '*') {
          breaker = 1;
          break;
        }
      if (breaker) break;
    }
    offset_r = offset_a_r - offset_b_r;
    offset_c = offset_a_c - offset_b_c;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++)
        if (b[i][j] == '*') {
          if (!In_Bounds(i + offset_r, j + offset_c)) {
            cout << "0\n";
            return;
          }
          if (a[i + offset_r][j + offset_c] != '*') {
            cout << "0\n";
            return;
          }
          a[i + offset_r][j + offset_c] = '.';
        }
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != '.') {
        cout << "0\n";
        return;
      }
  cout << "1\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}