#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int main() {
  io();

  int n;
  cin >> n;
  vi a(n), position(n + 1);

  for (int i = 0; i < n; i++)
    cin >> a[i];

  for (int i = 0; i < n; i++)
    position[a[i]] = i;

  int ans = 1;

  for (int i = 1; i < n; i++) 
    if (position[i + 1] < position[i])
      ans++;
  
  cout << ans << "\n";

  return 0;
}