#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;
stringstream ss;
vector<string> a, b;

bool Number(const string& p) {
  if (p.empty())
    return 0;
  if (p == "0")
    return 1;
  if (p[0] == '0')
    return 0;
  for (char c : p)
    if (!isdigit(c))
      return 0;
  return 1;
}

void Print(const vector<string>& v) {
  if (v.empty())
    cout << "-\n";
  else {
    cout << "\"";
    cout << v[0];
    for (int i = 1; i < v.size(); i++)
      cout << "," << v[i];
    cout << "\"\n";
  }
}

int main() {
  FASTIO();

  cin >> s;
  for (int i = 0; i < s.length(); i++)
    if (s[i] == ';')
      s[i] = ',';
  bool dollar = 0;
  if (!isalnum(s[s.length() - 1])) {
    s.push_back('$');
    dollar = 1;
  }
  ss << s;
  while (getline(ss, s, ',')) {
    if (Number(s))
      a.push_back(s);
    else
      b.push_back(s);
  }
  Print(a);
  if (dollar)
    b[b.size() - 1].pop_back();
  Print(b);

  return 0;
}