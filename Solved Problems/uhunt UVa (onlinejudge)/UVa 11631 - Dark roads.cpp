#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, root[N];
ll sum, mst;
vector<pair<int, ii>> EL;

int Root(int i) {
  return i == root[i] ? i : root[i] = Root(root[i]);
}

void U(int i, int j) {
  root[Root(i)] = Root(j);
}

bool Disjoint(int i, int j) {
  return Root(i) != Root(j);
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> m;
  if (!n && !m) return 0;
  EL.clear();
  int ux, vx, wx;
  sum = 0;
  for (int i = 0; i < m; i++) {
    cin >> ux >> vx >> wx;
    sum += wx;
    EL.push_back({ wx, { ux, vx } });
  }

  return 1;
}

#define w x.first
#define u x.second.first
#define v x.second.second

void Process() {
  mst = 0;
  sort(EL.begin(), EL.end());
  for (int i = 0; i <= n; i++)
    root[i] = i;
  for (pair<int, ii>& x : EL) {
    if (Disjoint(u, v)) {
      mst += w;
      U(u, v);
    }
  }
  cout << sum - mst << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}