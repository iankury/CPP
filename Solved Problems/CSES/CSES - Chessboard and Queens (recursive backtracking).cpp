#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int ans;
string s[8];

vi queen_on_col;

bool Share_Diag(int i, int j) {
  for (int k = 0; k < 8; k++)
    if (abs(i - queen_on_col[k]) == abs(j - k))
      return 1;
  return 0;
}

bool Read() {
  cin >> s[0];
  if (cin.eof())
    return 0;
  for (int i = 1; i < 8; i++)
    cin >> s[i];

  return 1;
}

void RB(int i) {
  if (i == 8)
    ans++;
  else {
    for (int j = 0; j < 8; j++) {
      if (s[i][j] == '*')
        continue;
      if (Share_Diag(i, j))
        continue;
      if (queen_on_col[j] >= 0)
        continue;
      queen_on_col[j] = i;
      RB(i + 1);
      queen_on_col[j] = -55;
    }
  }
}

void Process() {
  ans = 0;
  queen_on_col.assign(8, -55);
  RB(0);
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}