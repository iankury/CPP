#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100555, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
ii a[N];
int dr[255], dc[255];

int main() {
  FASTIO();

  dr['U'] = -1;
  dc['U'] = 0;
  dr['D'] = 1;
  dc['D'] = 0;
  dr['L'] = 0;
  dc['L'] = -1;
  dr['R'] = 0;
  dc['R'] = 1;
  dr['Z'] = -1;
  dc['Z'] = 1;
  dr['W'] = 1;
  dc['W'] = -1;
  int rep[6] = { 1, 1, 1, 1, 2, 1 };
  char cycle[6] = { 'L', 'U', 'Z', 'R', 'D', 'W' };
  a[1] = { 0, 0 };
  a[2] = { 0, 1 };
  int cyc_idx = 0;
  for (int i = 3; i < 100005;) {
    for (int j = 0; j < rep[cyc_idx]; i++, j++) {
      a[i].first = a[i - 1].first + dc[cycle[cyc_idx]];
      a[i].second = a[i - 1].second + dr[cycle[cyc_idx]];
    }
    cyc_idx++;
    if (cyc_idx == 6) {
      cyc_idx = 0;
      for (int j = 0; j < 6; j++)
        rep[j]++;
    }
  }

  while (cin >> n) {
    cout << a[n].first << " " << a[n].second << "\n";

    if (cin.eof())
      break;
  }

  return 0;
}