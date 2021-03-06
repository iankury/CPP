#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 26, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, a, b, pile[N], idx[N];
string s, t;
vi v[26];

void Recall(int p, int upto) {
  while (v[p].back() != upto) {
    idx[v[p].back()] = v[v[p].back()].size();
    pile[v[p].back()] = v[p].back();
    v[v[p].back()].push_back(v[p].back());
    v[p].pop_back();
  }
}

int main() {
  FASTIO();

  cin >> n;
  for (int i = 0; i < n; i++) {
    pile[i] = i;
    idx[i] = 0; 
    v[i].push_back(i);
  }
  while (cin >> s, s != "quit") {
    cin >> a >> t >> b;
    if (a == b || pile[a] == pile[b]) continue;
    if (s == "move") {
      Recall(pile[a], a);
      if (t == "onto") Recall(pile[b], b);
      v[pile[a]].pop_back();
      idx[a] = v[pile[b]].size();
      pile[a] = pile[b];
      v[pile[b]].push_back(a);
    }
    else {
      if (t == "onto") Recall(pile[b], b);
      int to_pop = v[pile[a]].size() - idx[a], backup_pile_a = pile[a];
      for (int i = idx[a]; i < v[backup_pile_a].size(); i++) {
        idx[v[backup_pile_a][i]] = v[pile[b]].size();
        pile[v[backup_pile_a][i]] = pile[b];
        v[pile[b]].push_back(v[backup_pile_a][i]);
      }
      for (int i = 0; i < to_pop; i++) v[backup_pile_a].pop_back(); 
    }
  }
  for (int i = 0; i < n; i++) {
    cout << i << ":";
    for (auto x : v[i]) cout << " " << x;
    cout << "\n";
  }

  return 0;
}