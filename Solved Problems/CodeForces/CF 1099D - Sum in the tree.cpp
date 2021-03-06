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

int n, pi[N];
ll a[N], s[N];
vi kids[N];
bool odd[N];

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 1; i <= n; i++)
    kids[i].clear();
  for (int i = 2; i <= n; i++) {
    cin >> pi[i];
    kids[pi[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++)
    cin >> s[i];

  return 1;
}

void Process() {
  a[1] = s[1];
  queue<int> Q;
  for (int child : kids[1])
    Q.push(child);
  int cur;
  ll min_s, ans = a[1];
  while (!Q.empty()) {
    cur = Q.front();
    Q.pop();
    min_s = 0x3f3f3f3f3f3f3f3f;
    if (kids[cur].empty())
      min_s = s[pi[cur]];
    else
      for (int child : kids[cur])
        min_s = min(min_s, s[child]);
    a[cur] = min_s - s[pi[cur]];
    if (a[cur] < 0) {
      cout << "-1\n";
      return;
    }
    s[cur] = a[cur] + s[pi[cur]];
    ans += a[cur];
    for (int child : kids[cur]) {
      a[child] = s[child] - s[cur];
      ans += a[child];
      for (int grandchild : kids[child])
        Q.push(grandchild);
    }
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}