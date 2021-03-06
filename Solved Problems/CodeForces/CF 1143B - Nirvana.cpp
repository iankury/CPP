#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 15, M = 1000000007, BIG = 0x3f3f3f3f;

vi digits;
int q;

int Rec(int p) {
  if (p == q)
    return digits[q];
  int x = p ? digits[p] - 1 : max(digits[p] - 1, 1);
  return max((int)pow(9, q - p) * x, digits[p] * Rec(p + 1));
}

int main() {
  FASTIO();

  string s;
  cin >> s;
  
  for (int i = 0; i < s.length(); i++)
    digits.push_back(s[i] - '0');
  q = digits.size() - 1;
  cout << Rec(0) << "\n";

  return 0;
}