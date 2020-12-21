#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class BigInt {
  void Clean_Zeroes(string& _a) {
    while (_a.length() > 1 && _a.back() == '0')
      _a.pop_back();
  }
  bool Abs_Greater_Equal(const string& _a, const string& _b) {
    int i = _a.length() - (_a[0] == '-');
    int j = _b.length() - (_b[0] == '-');
    if (i > j)
      return 1;
    if (i < j)
      return 0;
    i = (_a[0] == '-');
    j = (_b[0] == '-');
    while (i < _a.length()) {
      if (_a[i] > _b[j])
        return 1;
      if (_a[i] < _b[j])
        return 0;
      i++;
      j++;
    }
    return 1;
  }
  string Add(string _a, string _b, bool _output_neg) {
    if (_a[0] == '-')
      _a[0] = '0';
    if (_b[0] == '-')
      _b[0] = '0';
    string ans;
    int pot = 0;
    while (!_a.empty() || !_b.empty()) {
      if (!_a.empty()) {
        pot += (_a.back() - '0');
        _a.pop_back();
      }
      if (!_b.empty()) {
        pot += (_b.back() - '0');
        _b.pop_back();
      }
      ans.push_back((pot % 10) + '0');
      pot /= 10;
    }
    while (pot) {
      ans.push_back((pot % 10) + '0');
      pot /= 10;
    }
    Clean_Zeroes(ans);
    if (_output_neg && ans != "0")
      ans.push_back('-');
    reverse(begin(ans), end(ans));
    return ans;
  }
  string Subtract(string _minuend, string _subtrahend, bool _output_neg) {
    if (_minuend[0] == '-')
      _minuend[0] = '0';
    if (_subtrahend[0] == '-')
      _subtrahend[0] = '0';
    int cash, credit = 0, debit;
    string ans;
    while (!_minuend.empty() || !_subtrahend.empty()) {
      cash = debit = 0;
      if (!_minuend.empty()) {
        cash = (_minuend.back() - '0');
        _minuend.pop_back();
      }
      if (!_subtrahend.empty()) {
        debit = (_subtrahend.back() - '0');
        _subtrahend.pop_back();
      }
      cash -= credit;
      credit = 0;
      if (cash < debit) {
        cash += 10;
        credit++;
      }
      ans.push_back((cash - debit) + '0');
    }
    Clean_Zeroes(ans);
    if (_output_neg && ans != "0")
      ans.push_back('-');
    reverse(begin(ans), end(ans));
    return ans;
  }
  string Generic_Add(const string& _a, const string& _b, bool _invert_second) {
    bool neg1 = _a[0] == '-';
    bool neg2 = _b[0] == '-';
    if (_invert_second)
      neg2 = !neg2;
    if (neg1 == neg2) {
      if (neg1)
        return Add(_a, _b, 1);
      return Add(_a, _b, 0);
    }
    else if (neg1) {
      if (Abs_Greater_Equal(_b, _a))
        return Subtract(_b, _a, 0);
      return Subtract(_a, _b, 1);
    }
    if (Abs_Greater_Equal(_a, _b))
      return Subtract(_a, _b, 0);
    return Subtract(_b, _a, 1);
  }
public:
  string Add(const string& _a, const string& _b) {
    return Generic_Add(_a, _b, 0);
  }
  string Subtract(const string& _a, const string& _b) {
    return Generic_Add(_a, _b, 1);
  }
};

int ct = 0;
int n;
string s, v1, v2;

const int DPSIZE = 55;

string C[DPSIZE][DPSIZE];

void Build_C() {
  BigInt bi;
  for (int i = 0; i < DPSIZE; i++)
    C[i][0] = C[i][i] = "1";
  for (int i = 2; i < DPSIZE; i++)
    for (int j = 1; j < i; j++)
      C[i][j] = bi.Add(C[i - 1][j - 1], C[i - 1][j]);
}

bool Read() {
  cin >> s;

  return 1;
}

void Print_One(const string& c, int x1, int x2) {
  string sx1, sx2;
  if (x1 > 1)
    sx1 = "^" + to_string(x1);
  if (x2 > 1)
    sx2 = "^" + to_string(x2);
  if (c != "1")
    cout << c << '*';
  if (x1 && x2)
    cout << v1 << sx1 << '*' << v2 << sx2;
  else if (x2)
    cout << v2 << sx2;
  else
    cout << v1 << sx1;
}

void Process() {
  cout << "Case " << ++ct << ": ";
  int idx = s.find_first_of('+'), idx2 = s.find_first_of(')');
  v1 = s.substr(1, idx - 1);
  v2 = s.substr(idx + 1, idx2 - idx - 1);
  int xp = stoi(s.substr(idx2 + 2));
  for (int i = 0; i <= xp; i++) {
    if (i)
      cout << '+';
    Print_One(C[xp][i], xp - i, i);
  }
  cout << "\n";
}

int main() {
  FASTIO();

  Build_C();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}