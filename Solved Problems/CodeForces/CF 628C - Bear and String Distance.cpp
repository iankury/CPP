#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, k;
string s;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> k;
  cin >> s;

  return 1;
}

void Process() {
  int mx;
  for (int i = 0; k && i < n; i++) {
    mx = max(abs(s[i] - 'a'), abs(s[i] - 'z'));
    if (mx <= k) {
      k -= mx;
      if (s[i] + mx > 'z')
        s[i] -= mx;
      else
        s[i] += mx;
    }
    else {
      if (s[i] + k > 'z')
        s[i] -= k;
      else
        s[i] += k;
      k = 0;
    }
  }
  if (k)
    cout << "-1\n";
  else
    cout << s << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}