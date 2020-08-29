#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Movie {
  int l, r;
  Movie() {}
  bool operator < (const Movie& m) const { return r < m.r; }
};

int n, k;
vector<Movie> a;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> k;
  a.resize(n);
  for (int i = 0; i < n; i++)
    cin >> a[i].l >> a[i].r;

  return 1;
}

void Process() {
  int ans = 0;
  sort(begin(a), end(a));
  multiset<int> busy_till;
  for (int i = 0; i < k; i++)
    busy_till.insert(-1);
  multiset<int>::iterator obliterator;
  for (int i = 0; i < n; i++) {
    obliterator = busy_till.upper_bound(a[i].l);
    if (obliterator == busy_till.begin())
      continue;
    ans++;
    busy_till.erase(prev(obliterator));
    busy_till.insert(a[i].r);
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}