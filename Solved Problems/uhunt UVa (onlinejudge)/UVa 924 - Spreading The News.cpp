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

const int N = 2555, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, queries, sources[N];
vi adj[N];
vector<bool> vis;

bool Contains(int u, int v) {
  for (int i : adj[u])
    if (i == v) return 1;
  return 0;
}

bool Read() {
  cin >> n;
  if (cin.eof()) return 0;
  for (int i = 0; i < n; i++)
    adj[i].clear();
  int p, v;
  for (int i = 0; i < n; i++) {
    cin >> p;
    for (int j = 0; j < p; j++) {
      cin >> v;
      if (!Contains(i, v)) 
        adj[i].push_back(v);
    }
  }
  cin >> queries;
  for (int i = 0; i < queries; i++)
    cin >> sources[i];

  return 1;
}

struct Node {
  int key, layer;
};

void Process() {
  int max_boom, boom, day, last;
  Node cur;
  for (int i = 0; i < queries; i++) {
    vis.assign(n, 0);
    max_boom = boom = day = last = 0;
    queue<Node> Q;
    for (int v : adj[sources[i]]) 
      Q.push({ v, 1 });
    vis[sources[i]] = 1;
    while (!Q.empty()) {
      cur = Q.front();
      Q.pop();
      if (vis[cur.key]) continue;
      vis[cur.key] = 1;
      if (cur.layer != last) {
        last = cur.layer;
        boom = 1;
      }
      else boom++;
      if (boom > max_boom) {
        max_boom = boom;
        day = last;
      }
      for (int v : adj[cur.key]) 
        Q.push({ v, last + 1 });
    }
    if (last) cout << max_boom << " " << day << "\n";
    else cout << "0\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}