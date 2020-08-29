#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

const int K = 1e6 + 7;
int kmpb[K];
vi KMP(const string& T, const string& P) {
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
    if (j == P.length()) {
      ans.push_back(i - j);
      j = kmpb[j];
    }
  }
  return ans;
}

int main() {
  FASTIO();

  return 0;
}