#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
int ct = 0;
string s;

bool Read() {
  cin >> s;

  return 1;
}

void Process() {
  string a[110];
  n = s.length();
  cout << "Case #" << ++ct << ":\n";
  string x(n + 3, '-');
  x[0] = '+';
  int st = 55, en = 55;
  int cur = 55;
  for (int i = 0; i < n; i++) {
    while (a[cur].length() < i)
      a[cur].push_back(' ');
    if (s[i] == 'C') {
      a[cur].push_back('_');
      if (i < n - 1 && s[i + 1] == 'F')
        cur++;
    }
    else if (s[i] == 'R') {
      a[cur].push_back('/');
      if (i < n - 1 && s[i + 1] != 'F') 
        cur--;
    }
    else {
      a[cur].push_back('\\');
      if (i < n - 1 && s[i + 1] == 'F')
        cur++;
    }
    st = min(st, cur);
    en = max(en, cur);
  }
  for (int i = st; i <= en; i++)
    cout << "| " << a[i] << "\n";
  cout << x << "\n\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}