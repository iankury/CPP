#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
int m;
int ct = 0;

bool Read() {
  cin >> n;
  cin >> m;

  return 1;
}

string Wave() {
  string ans;
  for (int i = 1; i <= n; i++) {
    ans.append(string(i, i + '0'));
    ans.push_back('\n');
  }
  for (int i = n - 1; i > 0; i--) {
    ans.append(string(i, i + '0'));
    ans.push_back('\n');
  }
  return ans;
}

void Process() {
  if (ct++)
    cout << "\n";
  string w = Wave();
  for (int i = 0; i < m; i++) {
    if (i)
      cout << "\n";
    cout << w;
  }
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}