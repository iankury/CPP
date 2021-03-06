#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 11, M = 105, BIG = 0x3f3f3f3f;

int ct = 0;
int n, k, t[N];
int dist[N][M];
vector<vi> adj;
bool acc[M];

struct Node {
  int ele, flo, d;
  bool operator < (const Node& p) const {
    return d > p.d;
  }
};

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  cin >> k;
  for (int i = 1; i <= n; i++)
    cin >> t[i];
  memset(acc, 0, sizeof acc);
  adj.clear();
  adj.resize(n + 1);
  int v;
  string s;
  cin.ignore();
  for (int i = 1; i <= n; i++) {
    getline(cin, s);
    stringstream ss(s);
    while (ss >> v) {
      acc[v] = 1;
      adj[i].push_back(v);
    }
  }

  return 1;
}

void Process() {
  if (acc[k] == 0) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  memset(dist, BIG, sizeof dist);
  priority_queue<Node> Q;
  for (int i = 1; i <= n; i++) {
    dist[i][0] = 0;
    if (adj[i][0] == 0)
      Q.push({ i, 0, 0 });
  }
  Node u;
  vector<Node> v;
  while (!Q.empty()) {
    u = Q.top();
    Q.pop();
    for (int i = 1; i <= n; i++) 
      if (binary_search(adj[i].begin(), adj[i].end(), u.flo))
        v.push_back({ i, u.flo, u.d + 60 });
    for (int floor : adj[u.ele])
      v.push_back({ u.ele, floor, u.d + t[u.ele] * abs(u.flo - floor) });
    for (const Node& cand : v) 
      if (cand.d < dist[cand.ele][cand.flo]) {
        dist[cand.ele][cand.flo] = cand.d;
        Q.push(cand);
      }
  }
  int ans = BIG;
  for (int i = 1; i <= n; i++) 
    ans = min(ans, dist[i][k]);
  if (ans == BIG)
    cout << "IMPOSSIBLE\n";
  else
    cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}