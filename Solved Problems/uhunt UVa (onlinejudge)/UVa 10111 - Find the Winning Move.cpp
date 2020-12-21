#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;

bool Read() {
  char c;
  cin >> c;
  if (cin.eof() || c == '$')
    return 0;
  string r;
  s.clear();
  for (int i = 0; i < 4; i++) {
    cin >> r;
    s.append(r);
  }

  return 1;
}

char Enemy(char c) { return c == 'x' ? 'o' : 'x'; }

string Encode(int x) {
  char i = (x / 4) + '0';
  char j = (x % 4) + '0';
  return string{ '(', i, ',', j, ')' };
}

bool Win(char c) {
  if (c == 'o') {
    bool full = 1;
    for (int i = 0; i < 16; i++)
      if (s[i] == '.')
        full = 0;
    if (full)
      return 1;
  }
  for (int i = 0; i < 16; i += 4)
    if (s[i] == c && s[i + 1] == c && s[i + 2] == c && s[i + 3] == c)
      return 1;
  for (int i = 0; i < 4; i++)
    if (s[i] == c && s[i + 4] == c && s[i + 8] == c && s[i + 12] == c)
      return 1;
  return (s[0] == c && s[5] == c && s[10] == c && s[15] == c)
    || (s[3] == c && s[6] == c && s[9] == c && s[12] == c);
}

bool Rec(char c) {
  if (Win('x'))
    return 1;
  if (Win('o'))
    return 0;
  bool ans;
  if (c == 'x') {
    for (int i = 0; i < 16; i++)
      if (s[i] == '.') {
        s[i] = c;
        ans = Rec(Enemy(c));
        s[i] = '.';
        if (ans) 
          return 1;
      }
    return 0;
  }
  else {
    for (int i = 0; i < 16; i++)
      if (s[i] == '.') {
        s[i] = c;
        ans = Rec(Enemy(c));
        s[i] = '.';
        if (!ans)
          return 0;
      }
    return 1;
  }
  return 0;
}

void Process() {
  for (int i = 0; i < 16; i++) {
    if (s[i] != '.')
      continue;
    s[i] = 'x';
    if (Rec('o')) {
      cout << Encode(i) << "\n";
      return;
    }
    s[i] = '.';
  }
  cout << "#####\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}