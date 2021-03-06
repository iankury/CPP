#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }

vector<int> PrefixFunction(const string& s) {
  const auto m = s.length();
  vector<int> pi(m + 1);
  pi[0] = -1;
  int i = 0, j = -1;
  while (i < m) {
    while (j >= 0 && s[i] != s[j])
      j = pi[j];
    ++i; ++j;
    pi[i] = j;
  }
  return pi;
}

vector<int> KMP(const string& T, const string& P, const vector<int>& pi) {
  vector<int> ans;
  const auto n = T.length(), m = P.length();
  int i = 0, j = 0;
  while (i < n) {
    while (j >= 0 && T[i] != P[j])
      j = pi[j];
    ++i; ++j;
    if (j == m) {
      ans.push_back(i - j);
      j = pi[j];
    }
  }
  return ans;
}

int main() {
  io();

  return 0;
}