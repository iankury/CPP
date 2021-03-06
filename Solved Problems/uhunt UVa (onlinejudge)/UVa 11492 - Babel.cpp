#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, sz_encode, st, en;
map<string, int> encode;
vector<vi> dist;

struct Edge {
  int key, w;
  char c;
};
vector<vector<Edge>> adj;

struct Node {
  int key, d;
  char c;
  bool operator < (const Node& p) const {
    return d > p.d;
  }
};

int Encode(const string& p) {
  if (!encode.count(p))
    encode[p] = sz_encode++;
  return encode[p];
}

bool Read() {
  cin >> n;
  if (!n || cin.eof()) return 0;

  adj.clear();
  adj.resize(n << 2);
  encode.clear();
  sz_encode = 0;
  int u, v, w;
  string r, s, t;
  cin >> r >> s;
  st = Encode(r);
  en = Encode(s);
  for (int i = 0; i < n; i++) {
    cin >> r >> s >> t;
    u = Encode(r);
    v = Encode(s);
    w = t.length();
    adj[u].push_back({ v, w, t[0] });
    adj[v].push_back({ u, w, t[0] });
  }

  return 1;
}

void Process() {
  dist.assign(sz_encode, vi(26, BIG));
  priority_queue<Node> Q;
  Q.push({ st, 0, '$' });
  Node u, v;
  while (!Q.empty()) {
    u = Q.top();
    Q.pop();
    for (const Edge& edge : adj[u.key]) {
      if (edge.c == u.c) 
        continue;
      v = { edge.key, u.d + edge.w, edge.c };
      if (v.d < dist[v.key][v.c - 'a']) {
        dist[v.key][v.c - 'a'] = v.d;
        Q.push(v);
      }
    }
  }
  int ans = BIG;
  for (int i = 0; i < 26; i++)
    ans = min(ans, dist[en][i]);
  if (ans == BIG) 
    cout << "impossivel\n";
  else
    cout << ans << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}