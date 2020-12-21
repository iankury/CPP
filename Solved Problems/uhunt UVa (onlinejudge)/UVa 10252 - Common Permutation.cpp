#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int main() {
  FASTIO();

  string a, b;
  while (1) {
    getline(cin, a);
    if (cin.eof())
      break;
    getline(cin, b);
    int fa[26] = { 0 }, fb[26] = { 0 };
    for (char c : a)
      fa[c - 'a']++;
    for (char c : b)
      fb[c - 'a']++;
    for (int i = 0; i < 26; i++)
      cout << string(min(fa[i], fb[i]), i + 'a');
    cout << "\n";
  }

  return 0;
}