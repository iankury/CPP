#include <iostream>
#include <string>
#include <string.h>
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
int n;
vector<ll> l;

bool Read() {
  l.clear();
  ll p;
  while (cin >> p, p) 
    l.push_back(p);
  return 1;
}

void Process() {
  n = l.size();
  sort(l.begin(), l.end());
  ll ans = 0, pot = 0;
  for (ll x : l) {
    if (ans > 5000000) {
      cout << "Too expensive\n";
      return;
    }
    pot = 1;
    for (int i = 0; i < n; i++)
      pot *= x;
    ans += 2 * pot;
    n--;
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}