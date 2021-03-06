#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>
#include <sstream>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 205, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
string trash;
map<string, int> encode;
string decode[N];
bool vis[N];

bool Blank(const string& s) {
  for (char c : s)
    if (isalpha(c)) return 0;
  return 1;
}
struct Query { int x, y; };
vector<Query> queries;
vi adj[N];

bool Friends(const string& p, const string& q) {
  if (p.length() != q.length()) return 0;
  int dif_ct = 0;
  for (int i = 0; i < p.length(); i++)
    if (p[i] != q[i]) dif_ct++;
  return dif_ct == 1;
}

bool Read() {
  encode.clear();
  queries.clear();
  n = 0;
  string s, r;
  while (getline(cin, s)) {
    if (s[0] == '*') break;
    if (!encode.count(s)) {
      encode[s] = n;
      decode[n] = s;
      n++;
    }
  }
  while (getline(cin, s)) {
    if (Blank(s)) break;
    stringstream ss(s);
    ss >> r >> s;
    queries.push_back({ encode[r], encode[s] });
  }

  return 1;
}

#define u cur.first
#define layer cur.second
void Process() {
  if (ct++) cout << "\n";
  for (int i = 0; i < n; i++)
    adj[i].clear();
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) 
      if (Friends(decode[i], decode[j])) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
  for (Query& query : queries) {
    memset(vis, 0, sizeof vis);
    cout << decode[query.x] << " " << decode[query.y] << " ";
    queue<ii> Q;
    Q.push({ query.x, 0 });
    int ans = 0;
    ii cur{ 0, 0 };
    while (!Q.empty()) {
      cur = Q.front();
      Q.pop();
      if (vis[u]) continue;
      if (u == query.y) {
        ans = layer;
        break;
      }
      vis[u] = 1;
      for (int v : adj[u])
        Q.push({ v, layer + 1 });
    }
    cout << ans << "\n";
  }
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  getline(cin, trash);
  getline(cin, trash);
  while (Read() && T--) Process();

  return 0;
}