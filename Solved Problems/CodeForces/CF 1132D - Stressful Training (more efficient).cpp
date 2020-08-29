#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, k;
vector<ll> ax, b, a;
vector<vi> SX, S;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> k;
  a.resize(n);
  ax.resize(n);
  b.resize(n);
  SX.assign(k, vi());
  S.assign(k, vi());
  for (int i = 0; i < n; i++)
    cin >> ax[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];

  return 1;
}

void Process() {
  int st_idx = 0, laptop, idx;
  ll deadline;
  for (int i = 0; i < n; i++) {
    deadline = ax[i] / b[i] + 1;
    if (deadline < k) {
      st_idx = min(st_idx, (int)deadline);
      SX[deadline].push_back(i);
    }
  }
  ll p = 0, q = 2123456789123, mid;
  bool valid;
  while (p <= q) {
    mid = p + (q - p) / 2;
    valid = 1;
    idx = st_idx;
    a = ax;
    S = SX;
    for (int i = 0; i < k; i++) {
      while (idx < k && S[idx].empty()) 
        idx++;
      if (idx == i) {
        valid = 0;
        break;
      }
      if (idx >= k)
        break;
      laptop = S[idx].back();
      S[idx].pop_back();
      a[laptop] += mid;
      deadline = a[laptop] / b[laptop] + 1;
      if (deadline < k)
        S[deadline].push_back(laptop);
    }
    if (!valid)
      p = mid + 1;
    else if (p < q)
      q = mid;
    else {
      cout << mid << "\n";
      return;
    }
  }
  cout << "-1\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}