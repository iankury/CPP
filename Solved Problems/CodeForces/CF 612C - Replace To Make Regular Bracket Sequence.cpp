#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
string s;

bool Open(char c) {
  return c == '<' || c == '{' || c == '[' || c == '(';
}

bool Match(char p, char q) {
  return (p == '<' && q == '>') ||
         (p == '{' && q == '}') ||
         (p == '[' && q == ']') ||
         (p == '(' && q == ')');
}

void Process() {
  n = s.length();
  vector<char> S;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (Open(s[i]))
      S.push_back(s[i]);
    else {
      if (S.empty()) {
        cout << "Impossible\n";
        return;
      }
      if (!Match(S.back(), s[i]))
        ans++;
      S.pop_back();
    }
  }
  if (S.empty())
    cout << ans << "\n";
  else
    cout << "Impossible\n";
}

int main() {
  FASTIO();

  while (cin >> s) {
    Process();

    if (cin.eof())
      break;
  }

  return 0;
}