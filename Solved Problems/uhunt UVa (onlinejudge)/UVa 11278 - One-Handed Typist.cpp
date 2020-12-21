#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

string q = "1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";
string d = "123qjlmfp/[]456.orsuyb;=\\789aehtdck-0zx,inwvg'!@#QJLMFP?{}$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\"";

char encode[300];

int main() {
  FASTIO();

  memset(encode, 0, sizeof encode);

  for (int i = 0; i < q.length(); i++)
    encode[q[i]] = d[i];

  string s;
  while (getline(cin, s)) {
    for (int i = 0; i < s.length(); i++)
      if (encode[s[i]])
        s[i] = encode[s[i]];
    cout << s << "\n";
    if (cin.eof())
      break;
  }

  return 0;
}