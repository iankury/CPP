#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct xp {
  bool mu;
  string a, b;
};
int n, ct = 0;
unordered_map<string, xp> mp;
string last;

bool Read() {
  cin >> n;
  string s, a, b;
  xp cur;
  char c;
  mp.clear();
  for (int i = 0; i < n; i++) {
    cin >> s >> c >> a >> c >> b;
    cur = { c == '*', a, b };
    mp[s] = cur;
    if (i == n - 1)
      last = s;
  }

  return 1;
}

string Build(const string& s) {
  string ans, a = mp[s].a, b = mp[s].b;
  bool mu = mp[s].mu;
  if (mp.count(a)) {
    if (mp[a].mu == 0 && mu)
      ans = "(" + Build(a) + ")";
    else
      ans = Build(a);
  }
  else
    ans = a;
  if (mu)
    ans.push_back('*');
  else
    ans.push_back('+');
  if (mp.count(b)) {
    if (!(mu == 0 && mp[b].mu))
      ans += "(" + Build(b) + ")";
    else
      ans += Build(b);
  }
  else
    ans += b;
  return ans;
}

void Process() {
  cout << "Expression #" << ++ct << ": ";
  cout << Build(last) << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}