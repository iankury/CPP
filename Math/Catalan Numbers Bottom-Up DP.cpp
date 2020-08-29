#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Division_Output {
  string Quotient;
  string Remainder;
};

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
  bool Abs_Less_Equal(const string& _a, const string& _b) {
    int i = _a.length() - (_a[0] == '-');
    int j = _b.length() - (_b[0] == '-');
    if (i > j)
      return 0;
    if (i < j)
      return 1;
    i = (_a[0] == '-');
    j = (_b[0] == '-');
    while (i < _a.length()) {
      if (_a[i] < _b[j])
        return 1;
      if (_a[i] > _b[j])
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
  string Multiply(string _a, string _b) {
    if (Abs_Greater_Equal(_b, _a))
      swap(_a, _b);
    string ans;
    int st_a = (_a[0] == '-'), s;
    int mx = max(_a.length(), _b.length());
    bool neg = st_a != (_b[0] == '-');
    reverse(begin(_b), end(_b));
    if (_b.back() == '-')
      _b.pop_back();
    int i = _a.length() - 1, j = 0;
    int pot = 0;
    while (j < _b.length()) {
      for (int k = 0; k < mx; k++) {
        if (i + k < _a.length() && j + k < _b.length())
          pot += (_a[i + k] - '0') * (_b[j + k] - '0');
        else
          break;
      }
      ans.push_back((pot % 10) + '0');
      pot /= 10;
      if (i > st_a)
        i--;
      else
        j++;
    }
    while (pot) {
      ans.push_back((pot % 10) + '0');
      pot /= 10;
    }
    Clean_Zeroes(ans);
    if (neg && ans != "0")
      ans.push_back('-');
    reverse(begin(ans), end(ans));
    return ans;
  }
  Division_Output Divide(string _a, string _b) {
    string quotient, remainder, pfix, sfix, mxd, prod;
    bool one_more = 0, pending = 0;
    if (!Abs_Less_Equal(_b, _a))
      return { "0", _a };
    if ((_a[0] == '-') != (_b[0] == '-'))
      quotient = "-";
    if (_a[0] == '-')
      remainder = "-";
    if (_a[0] == '-')
      _a = _a.substr(1);
    if (_b[0] == '-')
      _b = _b.substr(1);
    pfix = _a.substr(0, _b.length());
    if (!Abs_Greater_Equal(pfix, _b)) {
      one_more = 1;
      pfix.push_back(_a[_b.length()]);
    }
    if (_a.length() > _b.length() + one_more)
      sfix = _a.substr(_b.length() + one_more);
    reverse(begin(sfix), end(sfix));
    do {
      pending = 0;
      for (int i = 9; i >= 0; i--) {
        mxd = to_string(i);
        prod = Multiply(_b, mxd);
        if (Abs_Less_Equal(prod, pfix))
          break;
      }
      quotient.push_back(mxd[0]);
      pfix = Subtract(pfix, prod);
      if (!sfix.empty()) {
        pending = 1;
        if (pfix == "0") {
          pfix[0] = sfix.back();
          sfix.pop_back();
        }
        else {
          pfix.push_back(sfix.back());
          sfix.pop_back();
        }
      }
    } while (!sfix.empty() || Abs_Greater_Equal(pfix, _b));
    if (pending)
      quotient.push_back('0');
    if (pfix == "0")
      return { quotient, "0" };
    remainder.append(pfix);
    return { quotient, remainder };
  }
};

const int DPMAX = 155;
string cat[DPMAX];
void Build_Cat() {
  BigInt bi;
  string num, den;
  cat[0] = "1";
  for (int i = 0; i < DPMAX - 1; i++) {
    num = to_string((ll)(i * 2 + 2) * (i * 2 + 1));
    den = to_string((i + 2) * (i + 1));
    cat[i + 1] = bi.Divide(bi.Multiply(cat[i], num), den).Quotient;
  }
}

int main() {
  FASTIO();

  Build_Cat();
  for (int i = 0; i < DPMAX; i++)
    cout << cat[i] << "\n";

  return 0;
}