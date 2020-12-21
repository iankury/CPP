#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

const int K = 1e6 + 7;
int kmpb[K];
int KMP(const string& T, const string& P) {
  int i = 0, j;
  j = kmpb[0] = -1;
  while (i < P.length()) {
    while (j >= 0 && P[i] != P[j])
      j = kmpb[j];
    i++; j++;
    kmpb[i] = j;
  }
  i = j = 0;
  while (i < T.length()) {
    while (j >= 0 && T[i] != P[j])
      j = kmpb[j];
    i++; j++;
    if (i == T.length()) 
      return j;
  }
  return -1;
}

int n;
int k;
string s[N];

bool Read() {
  cin >> k >> n;
  for (int i = 0; i < n; i++)
    cin >> s[i];

  return 1;
}

void Process() {
  int ans = s[0].length();
  for (int i = 1; i < n; i++)
    ans += s[i].length() - KMP(s[i - 1], s[i]);
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}