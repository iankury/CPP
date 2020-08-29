#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct Node {
  ll a, b;
  bool operator < (const Node& node) const {
    return (double)a / b > (double)node.a / node.b;
  }
};
priority_queue<Node> QX;

int ct = 0;
int n, k;
vector<ll> ax;
ll mxb;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  while (!QX.empty())
    QX.pop();
  ax.resize(n);
  cin >> k;
  ll bx;
  mxb = 0;
  for (int i = 0; i < n; i++)
    cin >> ax[i];
  for (int i = 0; i < n; i++) {
    cin >> bx;
    mxb = max(mxb, bx);
    if (bx * k > ax[i])
      QX.push({ ax[i], bx });
  }

  return 1;
}

void Process() {
  ll p = 0, q = mxb * n + 5 , mid, a, b;
  bool valid;
  while (p <= q) {
    mid = p + (q - p) / 2;
    valid = 1;
    priority_queue<Node> Q = QX;
    for (int i = 0; i < k && !Q.empty(); i++) {
      a = Q.top().a;
      b = Q.top().b;
      Q.pop();
      if (a - b * i < 0) {
        valid = 0;
        break;
      }
      a += mid;
      if (b * k > a)
        Q.push({ a, b });
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