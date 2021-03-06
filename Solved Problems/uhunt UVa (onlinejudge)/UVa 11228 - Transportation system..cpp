#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, r, y[N], x[N], root[N];
vector<pair<double, ii>> EdgeList;
#define weight EdgeList[i].first
#define u EdgeList[i].second.first
#define v EdgeList[i].second.second

int Root(int i) {
  return root[i] == i ? i : root[i] = Root(root[i]);
}

void U(int i, int j) {
  root[Root(i)] = Root(j);
}

bool Disjoint(int i, int j) {
  return Root(i) != Root(j);
}

int Count_DS() {
  set<int> S;
  for (int i = 0; i < n; i++)
    S.insert(Root(i));
  return S.size();
}

double D(double ix, double iy, double jx, double jy) {
  return sqrt(pow(abs(ix - jx), 2) + pow(abs(iy - jy), 2));
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> r;
  for (int i = 0; i < n; i++)
    cin >> x[i] >> y[i];

  return 1;
}


void Process() {
  for (int i = 0; i <= n; i++)
    root[i] = i;
  EdgeList.clear();
  cout << "Case #" << ++ct << ": ";
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      EdgeList.push_back({ D(x[i], y[i], x[j], y[j]), { i, j } });
  sort(EdgeList.begin(), EdgeList.end());

  int i = 0, number_of_states = 0;
  double sum_roads = 0., sum_highways = 0.;
  for (; i < EdgeList.size(); i++) { 
    if (weight > r) break;
    if (Disjoint(u, v)) {
      U(u, v);
      sum_roads += weight;
    }
  }
  number_of_states = Count_DS();
  for (; i < EdgeList.size(); i++) {
    if (Disjoint(u, v)) {
      U(u, v);
      sum_highways += weight;
    }
  }
  cout << fixed << setprecision(0) << number_of_states << " " << 
    sum_roads << " " << sum_highways << "\n";
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  while (Read() && T--) Process();

  return 0;
}