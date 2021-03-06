#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <map>
#include <sstream>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 22, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
bool vis[N];
vi adj[N];
vector<char> nodes_int_to_char;
map<char, int> nodes_char_to_int;
set<string> poss;
string ts;

bool Read() {
  nodes_char_to_int.clear();
  nodes_int_to_char.clear();
  string s;
  getline(cin, s);
  getline(cin, s);
  for (char c : s)
    if (isalpha(c))
      nodes_int_to_char.push_back(c);
  n = nodes_int_to_char.size();
  for (int i = 0; i < n; i++) {
    adj[i].clear();
    nodes_char_to_int[nodes_int_to_char[i]] = i;
  }
  getline(cin, s);
  vector<string> tokens;
  stringstream ss(s);
  while (ss >> s)
    tokens.push_back(s);
  int u, v;
  for (const string& token : tokens) {
    u = nodes_char_to_int[token[0]];
    v = nodes_char_to_int[token[2]];
    adj[u].push_back(v);
  }
  return 1;
}

bool Cycle(int u, int st) {
  if (vis[u])
    return st == u;
  vis[u] = 1;
  for (int v : adj[u])
    if (Cycle(v, st))
      return 1;
  return 0;
}

void DFS(int u) {
  if (vis[u]) return;
  vis[u] = 1;
  for (int v : adj[u])
    DFS(v); 
  ts.push_back(nodes_int_to_char[u]);
}

void Process() {
  if (ct++) cout << "\n";
  poss.clear();
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < n; i++)
    if (!vis[i])
      if (Cycle(i, i)) {
        cout << "NO\n";
        return;
      }
  vi idc(n);
  for (int i = 0; i < n; i++)
    idc[i] = i;
  do {
    ts.clear();
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; i++)
      DFS(idc[i]);
    reverse(ts.begin(), ts.end());
    poss.insert(ts);
  } while (next_permutation(idc.begin(), idc.end()));
  for (const string& s : poss) {
    cout << s[0];
    for (int i = 1; i < s.length(); i++)
      cout << " " << s[i];
    cout << "\n";
  }
}

int main() {
  FASTIO();

  int T = 1;
  cin >> T;
  string trash;
  getline(cin, trash);
  while (Read() && T--) Process();

  return 0;
}