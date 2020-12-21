#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int K = 1e5 + 7;
int kmpb[K];
int KMP(const string& T, const string& P) {
  vi ans;
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
    if (i == T.length()) {
      return j;
    }
  }
  return -1;
}

int n;
string s, r;

void Process() {
  r = s;
  reverse(begin(r), end(r));
  n = s.length();
  int kmp = KMP(s, r);
  cout << s << r.substr(kmp) << "\n";
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