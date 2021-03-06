#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 2000075;
int n;
vi stk;
set<vi> ans;

void Backtrack(int p) {
  if (p == 1) {
    vi temp = stk;
    sort(temp.begin(), temp.end());
    ans.insert(temp);
  }
  else {
    vi div;
    int d;
    for (d = 2; d * d < p; d++) 
      if (p % d == 0) {
        div.push_back(d);
        div.push_back(p / d);
      }
    if (d * d == p)
      div.push_back(d);
    div.push_back(p);
    for (int d : div) {
      stk.push_back(d);
      Backtrack(p / d);
      stk.pop_back();
    }
  }
}

bool Read() {
  cin >> n;
  if (!n)
    return 0;

  return 1;
}

void Process() {
  ans.clear();
  Backtrack(n);
  ans.erase(*ans.rbegin());
  cout << ans.size() << "\n";
  if (ans.size()) {
    for (const vi& v : ans) {
      for (int i = 0; i < v.size(); i++) {
        if (i) cout << " ";
        cout << v[i];
      }
      cout << "\n";
    }
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}