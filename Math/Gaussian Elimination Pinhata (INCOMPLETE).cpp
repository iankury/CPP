#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 25, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m;

ll GCD(ll p, ll q) { return q ? GCD(q, p % q) : p; }

ll LCM(ll p, ll q) { return p * q / GCD(p, q); }

struct Fraction {
  ll num, den;
  Fraction() : num(0), den(1) {}
  Fraction(const string& s) {
    den = 1ll;
    size_t idx = s.find_first_of('/');
    if (idx == string::npos)
      num = stoll(s);
    else {
      num = stoll(s.substr(0, idx));
      den = stoll(s.substr(idx + 1));
    }
  }
  Fraction(ll _num, ll _den) : num(_num), den(_den) {}
  operator string() {
    if (den == 1)
      return to_string(num);
    string ans = to_string(num);
    ans.push_back('/');
    ans.append(to_string(den));
    return ans;
  }
};
Fraction a[N][N];

Fraction Reduce(const Fraction& p) {
  ll g = GCD(p.num, p.den);
  return { p.num / g, p.den / g };
}

Fraction Handle_Sign(const Fraction& p) {
  if (p.den < 0) 
    return { p.num * (-1ll), p.den * (-1ll) };
  return p;
}

Fraction Inverse(const Fraction& p) {
  return { p.den, p.num };
}

Fraction Product(const Fraction& p, const Fraction& q) {
  Fraction ans = { p.num * q.num, p.den * q.den };
  return Handle_Sign(Reduce(ans));
}

Fraction Quotient(const Fraction& p, const Fraction& q) {
  return Product(p, Inverse(q));
}

Fraction Sum(const Fraction& p, const Fraction& q) {
  ll l = LCM(p.den, q.den);
  return Handle_Sign(Reduce({ p.num * (l / p.den) + q.num * (l / q.den), l }));
}

Fraction Difference(const Fraction& p, const Fraction& q) {
  return Sum(p, { q.num * (-1ll), q.den });
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  m = n + 1;
  string s;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> s;
      a[i][j] = Fraction(s);
    }

  return 1;
}

void Process() {
  for (int i = 0; i < n; i++) 
    for (int ix = i + 1; ix < n; ix++) {
      Fraction k = Quotient(a[ix][i], a[i][i]);
      for (int j = 0; j < m; j++) 
        a[ix][j] = Difference(a[ix][j], Product(k, a[i][j]));
    }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cout << setw(7) << right << (string)a[i][j] << " ";
    cout << "\n";
  }
  // Agora falta fazer a back substitution
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}