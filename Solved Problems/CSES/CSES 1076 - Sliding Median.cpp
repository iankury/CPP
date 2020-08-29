#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
int k;
int a[N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  if (k == 1) {
    for (int i = 0; i < n; i++)
      cout << a[i] << " ";
    cout << "\n";
    return;
  }
  vi v(k);
  for (int i = 0; i < k; i++)
    v[i] = a[i];
  sort(begin(v), end(v));
  int mid = k / 2 - !(k % 2);
  multiset<int> s1, s2;
  for (int i = 0; i <= mid; i++)
    s1.insert(v[i]);
  for (int i = mid + 1; i < k; i++)
    s2.insert(v[i]);
  cout << v[mid] << " ";
  int j;
  multiset<int>::iterator it;
  for (int i = k; i < n; i++) {
    j = i - k;
    if (s1.size() <= s2.size())
      s1.insert(a[i]);
    else
      s2.insert(a[i]);
    it = s1.find(a[j]);
    if (it == s1.end()) {
      it = s2.find(a[j]);
      s2.erase(it);
    }
    else
      s1.erase(it);
    while (s1.size() > s2.size() + (k % 2)) {
      it = s1.end();
      it--;
      s2.insert(*it);
      s1.erase(it);
    }
    while (s1.size() < s2.size() + (k % 2)) {
      s1.insert(*s2.begin());
      s2.erase(s2.begin());
    }
    while (*s1.rbegin() > *s2.begin()) {
      s1.insert(*s2.begin());
      s2.insert(*s1.rbegin());
      it = s1.end();
      it--;
      s1.erase(it);
      s2.erase(*s2.begin());
    }
    cout << *s1.rbegin() << " ";
  }
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}