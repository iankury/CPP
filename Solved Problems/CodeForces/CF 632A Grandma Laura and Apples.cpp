#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
stack<bool> S;
ll n, p, ans, apples, gifts;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> p;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    S.push(s.length() > 5);
  }

  return 1;
}

void Process() {
  gifts = apples = 0;
  bool b;
  while (!S.empty()) {
    b = S.top();
    S.pop();
    if (b) {
      gifts++;
      apples = (2ll * apples) + 1ll;
    }
    else
      apples *= 2ll;
  }
  ans = apples * p - gifts * p / 2;
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}