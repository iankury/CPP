#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

void Recur(int origin, int buffer, int target, int disks) {
  if (disks == 1) 
    cout << origin << " " << target << "\n";
  else {
    Recur(origin, target, buffer, disks - 1);
    cout << origin << " " << target << "\n";
    Recur(buffer, origin, target, disks - 1);
  }
}

int main() {
  io();

  int n;
  cin >> n;

  cout << int(.5 + pow(2, n) - 1) << "\n";
  Recur(1, 2, 3, n);

  return 0;
}