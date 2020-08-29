#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class Cycle_Finder {
  enum { WHITE, GRAY, BLACK };
  vi color, cycle;
  int idx;
  const vector<vi>& adj;
  void DFS(int u) {
    if (color[u] == BLACK)
      return;
    color[u] = GRAY;
    for (int v : adj[u]) {
      if (color[v] == GRAY) {
        idx = v;
        cycle.push_back(v);
        break;
      }
      DFS(v);
      if (idx != -1)
        break;
    }
    if (idx != -1 && color[idx] == GRAY) 
      cycle.push_back(u);
    color[u] = BLACK;
  }
public:
  Cycle_Finder(const vector<vi>& adj) : adj(adj) {}
  vi Cycle() {
    idx = -1;
    color.assign(adj.size(), WHITE);
    for (int i = 1; i < adj.size(); i++) {
      DFS(i);
      if (!cycle.empty()) {
        reverse(begin(cycle), end(cycle));
        break;
      }
    }
    return cycle;
  }
};

int n, m;
vector<vi> adj;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  int u, v;
  adj.assign(n + 1, vi());
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  return 1;
}

void Process() {
  Cycle_Finder cf(adj);
  vi cycle = cf.Cycle();
  if (cycle.empty())
    cout << "No cycles.\n";
  else {
    cout << cycle.size() << "\n";
    for (int x : cycle)
      cout << x << " ";
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}