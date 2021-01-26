#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

// ↓ Adapted from Laaksonen's handbook
vi Z_Array(const string& s) { 
  int x = 0, y = 0, n = s.size();
  vi z(n);

  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - x], y - i + 1));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      x = i; 
      y = i + z[i]; 
      z[i]++;
    }
  }

  return z;
}

int main() {
  io();

  return 0;
}