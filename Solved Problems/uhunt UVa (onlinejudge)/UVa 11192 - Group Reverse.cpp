#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
string s, cur;

bool Read() {
  cin >> n;
  if (!n || cin.eof()) return 0;
  cin >> s;

  return 1;
}

void Process() {
  int wdt = s.length() / n;
  for (int i = 0; i < s.length(); i += wdt) {
    cur = s.substr(i, wdt);
    reverse(cur.begin(), cur.end());
    cout << cur;
  }
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}