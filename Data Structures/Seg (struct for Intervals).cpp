#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct Seg { // Attention: interval is [L,R)
  int L, R;
  operator bool() const {
    return L < R;
  }
  bool operator == (const Seg& p) const {
    return L == p.L && R == p.R;
  }
};

Seg Intersection(const Seg& p, const Seg& q) {
  if (p.R <= q.L || q.R <= p.L)
    return { 0, 0 };
  if (p.L <= q.L && p.R >= q.R)
    return q;
  if (q.L <= p.L && q.R >= p.R)
    return p;
  if (p.R < q.R)
    return { q.L, p.R };
  return { p.L, q.R };
}

pair<Seg, Seg> Difference(const Seg& p, const Seg& q) {
  if (p.R <= q.L || q.R <= p.L)
    return { { 0, 0 }, { 0, 0 } };
  if (p.L <= q.L && p.R >= q.R)
    return { { p.L, q.L }, { q.R, p.R } };
  if (q.L <= p.L && q.R >= p.R)
    return { { q.L, p.L }, { p.R, q.R } };
  if (p.R < q.R)
    return { { p.L, q.L}, { p.R, q.R } };
  return { { q.L, p.L }, { q.R, p.R } };
}

int main() {
  FASTIO();

  

  return 0;
}