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

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, incoming[N];
vi adj[N], ts;
priority_queue<int> Q;

bool Read() {
  memset(incoming, 0, sizeof incoming);
  cin >> n;
  if (cin.eof()) return 0;
  int u, v;
  for (int i = 0; i < n; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    incoming[v]++;
  }

  return 1;
}

void Process() {
  for (int i = 0; i < n; i++)
    if (!incoming[i])
      Q.push(i);
  while (!Q.empty()) {
    int u = Q.top();
    Q.pop();
    ts.push_back(u);
    for (int v : adj[u])
      if (--incoming[v] == 0)
        Q.push(v);
  }
  for (int u : ts)
    cout << u << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}