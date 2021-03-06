#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, u, freq[N], greq[N];

int main() {
  FASTIO();

  memset(freq, 0, sizeof freq);
  memset(greq, 0, sizeof greq);
  int ans = 0;
  set<int> S;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> u;
    freq[u]++;
    greq[freq[u]]++;
    greq[freq[u] - 1]--;
    S.insert(freq[u]);
    if (greq[freq[u] - 1] == 0)
      S.erase(freq[u] - 1);
    if (freq[u] == n || (S.size() == 1 && freq[u] == 1)) 
      ans = i;
    else if (S.size() == 2) {
      auto it = S.begin();
      int p = *it;
      it++;
      int q = *it;
      if (p == 1 && greq[p] == 1)
        ans = i;
      else if (q == 1 && greq[q] == 1)
        ans = i;
      else if (p == q + 1 && greq[p] == 1)
        ans = i;
      else if (q == p + 1 && greq[q] == 1)
        ans = i;
    }
  }
  cout << ans << "\n";

  return 0;
}