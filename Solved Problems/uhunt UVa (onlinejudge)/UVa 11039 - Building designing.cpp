#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 500005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
vi a[2];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  a[0].clear();
  a[1].clear();
  int u;
  for (int i = 0; i < n; i++) {
    cin >> u;
    if (u < 0)
      a[0].push_back(u * (-1));
    else
      a[1].push_back(u);
  }

  return 1;
}

void Process() {
  if (a[0].empty()) {
    if (a[1].empty())
      cout << "0\n";
    else
      cout << "1\n";
    return;
  }
  if (a[1].empty()) {
    cout << "1\n";
    return;
  }
  int i[2] = { 0, 0 }, ans = 1, bound = 0;
  bool turn;
  sort(a[1].begin(), a[1].end(), greater<int>());
  sort(a[0].begin(), a[0].end(), greater<int>());
  if (a[0][0] < a[1][0]) {
    bound = a[1][0];
    i[1]++;
    turn = 0;
  }
  else { 
    bound = a[0][0];
    i[0]++;
    turn = 1;
  }
  while (1) {
    while (i[turn] < a[turn].size() && a[turn][i[turn]] > bound) 
      i[turn]++;
    if (i[turn] >= a[turn].size())
      break;
    bound = a[turn][i[turn]];
    i[turn]++;
    turn = !turn;
    ans++;
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (Read() && T--)
    Process();

  return 0;
}