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

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, a[N], p[N], s[N];
vi maxpats;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cin >> m;
  for (int i = 1; i <= m; i++)
    cin >> p[i] >> s[i];

  return 1;
}

void Process() {
  int ans = 0, k = 1, strongest, streak;
  maxpats.assign(n + 1, 0);
  for (int i = 1; i <= m; i++)
    maxpats[s[i]] = max(maxpats[s[i]], p[i]);
  for (int i = n - 1; i > 0; i--)
    maxpats[i] = max(maxpats[i], maxpats[i + 1]);
  while (k <= n) {
    ++ans;
    streak = 0;
    strongest = a[k];
    while (k + streak <= n && maxpats[streak + 1] >= strongest) {
      streak++;
      strongest = max(strongest, a[k + streak]);
    }
    if (!streak) {
      cout << "-1\n";
      return;
    }
    k += streak;
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