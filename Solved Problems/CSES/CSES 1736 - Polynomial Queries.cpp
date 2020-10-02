#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct Seg { // [L, R)
  int L, R;
  int Len() const { return R - L; }
  operator bool() const { return L < R; }
  bool operator == (const Seg& s) const { return L == s.L && R == s.R; }
  Seg operator and (const Seg& s) const { // Intersection
    if (R <= s.L || s.R <= L)
      return { 0, 0 };
    if (L <= s.L && R >= s.R)
      return s;
    if (s.L <= L && s.R >= R)
      return { L, R };
    if (R < s.R)
      return { s.L, R };
    return { L, s.R };
  }
};

inline ll AP_Sum(ll a1, int an, int n) { return (a1 + an) * n / 2; }

struct Node {
  int starting = 0, ending = 0, weight = 0;
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, q, x, y, t;
  cin >> n >> q;
  vector<ll> a(n + 1), psa(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    psa[i] = psa[i - 1] + a[i];
  const int batch = 447, lim = q / batch + 1;
  for (int i = 0; i < lim; i++) {
    const int batch_start = batch * i;
    const int next_batch_start = batch_start + batch;
    vector<Seg> segs;
    vector<Node> nodes(n + 2);
    for (int j = batch_start; j < next_batch_start && j < q; j++) {
      cin >> t >> x >> y;
      if (t == 1) {
        segs.push_back({ x, y + 1 });
        nodes[x].starting++;
        nodes[y + 1].ending++;
        nodes[y + 1].weight += y + 1 - x;
      }
      else {
        ll sum = psa[y] - psa[x - 1];
        for (const Seg& s : segs) {
          const Seg intersection = Seg{ x, y + 1 } and s;
          if (intersection) {
            const int len = intersection.Len();
            const int a1 = x >= s.L ? x + 1 - s.L : 1;
            sum += AP_Sum(a1, a1 + len - 1, len);
          }
        }
        cout << sum << "\n";
      }
    }

    ll delta = 0, running = 0;

    for (int i = 1; i <= n; i++) {
      running -= nodes[i].ending;
      delta -= nodes[i].weight;
      running += nodes[i].starting;
      delta += running;
      a[i] += delta;
    }

    for (int i = 1; i <= n; i++)
      psa[i] = psa[i - 1] + a[i];
  }

  return 0;
}