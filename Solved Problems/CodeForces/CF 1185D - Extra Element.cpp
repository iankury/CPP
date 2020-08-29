#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Node {
  int idx, value;
  bool operator < (const Node& node) const {
    return value < node.value;
  }
};

int ct = 0;
int n;
Node a[N];
map<int, int> freq;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i].value;
    a[i].idx = i + 1;
  }

  return 1;
}

void Process() {
  sort(a, a + n);
  for (int i = 1; i < n; i++) 
    freq[a[i].value - a[i - 1].value]++;
  if (freq.size() > 3) {
    cout << "-1\n";
    return;
  }
  if (freq.size() == 1) {
    cout << a[0].idx << "\n";
    return;
  }
  int pending = 0, mx = 0;
  vi r;
  for (ii x : freq) {
    pending += x.second;
    if (x.second > mx) {
      mx = x.second;
      r.clear();
      r.push_back(x.first);
    }
    else if (x.second == mx) 
      r.push_back(x.first);
    mx = max(mx, x.second);
  }
  pending -= mx;
  if (pending > 2) {
    cout << "-1\n";
    return;
  }
  for (int x : r) {
    if (pending == 1) {
      for (int i = 1; i < n - 1; i++) 
        if (a[i].value - a[i - 1].value != x &&
            a[i + 1].value - a[i - 1].value == x) {
          cout << a[i].idx << "\n";
          return;
        }
      if (a[1].value - a[0].value != x) {
        cout << a[0].idx << "\n";
        return;
      }
      if (a[n - 1].value - a[n - 2].value != x) {
        cout << a[n - 1].idx << "\n";
        return;
      }
    }
    else {
      for (int i = 1; i < n - 1; i++)
        if (a[i].value - a[i - 1].value != x &&
            a[i + 1].value - a[i].value != x &&
            a[i + 1].value - a[i - 1].value == x) {
          cout << a[i].idx << "\n";
          return;
        }
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