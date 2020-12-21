#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
string p, s, t;
char a[3];
int encode[26];

bool Read() {
  cin >> p;
  if (cin.eof())
    return 0;
  cin >> s >> a[0] >> a[1] >> a[2] >> t;

  return 1;
}

string A(string x, string y) {
  reverse(begin(x), end(x));
  reverse(begin(y), end(y));
  string ans;
  bool carry = 0;
  int sum;
  for (int i = 0; i < max(x.length(), y.length()); i++) {
    sum = carry;
    carry = 0;
    if (i < x.length())
      sum += encode[x[i] - 'A'];
    if (i < y.length())
      sum += encode[y[i] - 'A'];
    if (sum == 0)
      ans.push_back('V');
    else if (sum == 1)
      ans.push_back('U');
    else if (sum == 2)
      ans.push_back('C');
    else if (sum == 3)
      ans.push_back('D');
    else if (sum == 4) {
      ans.push_back('V');
      carry = 1;
    }
    else if (sum == 5) {
      ans.push_back('U');
      carry = 1;
    }
    else if (sum == 6) {
      ans.push_back('C');
      carry = 1;
    }
    else {
      ans.push_back('D');
      carry = 1;
    }
  }
  if (carry)
    ans.push_back('U');
  reverse(begin(ans), end(ans));
  return ans;
}

void Process() {
  int vs = 0;
  for (int i = 0; i < 3; i++) {
    if (a[i] == 'A')
      s = A(s, p);
    else if (a[i] == 'R') 
      s.pop_back();
    else if (a[i] == 'L')
      s.push_back('V');
  }
  reverse(begin(s), end(s));
  reverse(begin(t), end(t));
  while (!s.empty() && s.back() == 'V')
    s.pop_back();
  while (!t.empty() && t.back() == 'V')
    t.pop_back();
  if (s == t)
    cout << "YES\n";
  else
    cout << "NO\n";
}

int main() {
  FASTIO();

  encode['V' - 'A'] = 0;
  encode['U' - 'A'] = 1;
  encode['C' - 'A'] = 2;
  encode['D' - 'A'] = 3;

  cout << "COWCULATIONS OUTPUT\n";
  int T;
  cin >> T;
  while (T-- && Read())
    Process();
  cout << "END OF OUTPUT\n";

  return 0;
}