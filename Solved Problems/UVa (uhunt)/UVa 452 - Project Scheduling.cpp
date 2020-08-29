#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 27, M = 1000000007, BIG = 0x3f3f3f3f;

struct Edge {
  int v, w;
};

int ct = 0;
int n;
int dp[N];
bool vis[N];
vector<string> lines;
string s;
stringstream ss;
vector<vector<Edge>> adj;
vi topo;

bool Blank(const string& _s) {
  if (_s.empty())
    return 1;
  for (char c : _s)
    if (!isblank(c) && c != '\n')
      return 0;
  return 1;
}

bool Read() {
  lines.clear();
  while (getline(cin, s)) {
    if (Blank(s))
      break;
    lines.push_back(s);
  }

  return 1;
}

void DFS(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (const Edge& ed : adj[u])
    DFS(ed.v);
  topo.push_back(u);
}

void Process() {
  if (ct++)
    cout << "\n";
  int ans = 0;
  memset(dp, 0, sizeof dp);
  adj.assign(N, vector<Edge>());
  char cu, cv;
  int w;
  for (const string& line : lines) {
    ss = stringstream(line);
    ss >> cv >> w;
    dp[cv - 'A'] = w * (-1);
    while (ss >> cu) 
      adj[cu - 'A'].push_back({cv - 'A', w * (-1)});
    ans = min(ans, w * (-1));
  }
  topo.clear();
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < 27; i++)
    DFS(i);
  reverse(begin(topo), end(topo));
  for (int u : topo)
    for (const Edge& ed : adj[u]) {
      dp[ed.v] = min(dp[ed.v], dp[u] + ed.w);
      ans = min(ans, dp[ed.v]);
    }
  ans *= -1;
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  getline(cin, s);
  getline(cin, s);
  while (T-- && Read())
    Process();

  return 0;
}