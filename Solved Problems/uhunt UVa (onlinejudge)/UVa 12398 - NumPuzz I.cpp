#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int a[3][3];
string s;

bool In_Bounds(int i, int j) {
  return i >= 0 && i < 3 && j >= 0 && j < 3;
}

void Raise(int i, int j) {
  if (In_Bounds(i, j)) a[i][j] = (a[i][j] + 1) % 10;
}

int main() {
  FASTIO();

  while (getline(cin , s)) {
    cout << "Case #" << ++ct << ":\n";
    memset(a, 0, sizeof a);
    for (int i = s.length() - 1; i >= 0; i--) {
      if (isalpha(s[i])) {
        int cur = s[i] - 'a';
        int r = cur / 3, c = cur % 3;
        Raise(r, c);
        Raise(r + 1, c);
        Raise(r - 1, c);
        Raise(r, c + 1);
        Raise(r, c - 1);
      }
    }
    for (int i = 0; i < 3; i++)
      cout << a[i][0] << " " << a[i][1] << " " << a[i][2] << "\n";
  }

  return 0;
}