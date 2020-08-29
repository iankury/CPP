#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const ll BIG = 0x3f3f3f3f3f3f3f3f;

int n, m;
vector<ll> d;
vi pi;

struct Edge {
  int u, v;
  ll w;
};
vector<Edge> edge_list;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  edge_list.resize(m);
  for (int i = 0; i < m; i++)
    cin >> edge_list[i].u >> edge_list[i].v >> edge_list[i].w;

  return 1;
}

vi Negative_Cycle() {
  d.assign(n + 1, BIG);
  pi.resize(n + 1);
  int idx;
  for (int i = 0; i < n; i++) {
    idx = -1;
    for (const Edge& ed : edge_list) {
      if (d[ed.u] + ed.w < d[ed.v]) {
        pi[ed.v] = ed.u;
        d[ed.v] = d[ed.u] + ed.w;
        idx = ed.v;
      }
    }
  }
  vi ans;
  if (idx != -1) {
    for (int i = 0; i < n; i++)
      idx = pi[idx];
    ans.push_back(idx);
    do {
      idx = pi[idx];
      ans.push_back(idx);
    } while (idx != ans[0]);
    reverse(begin(ans), end(ans));
  }
  return ans;
}

void Process() {

}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}