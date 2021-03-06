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

const int N = 205, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
map<string, int> encode;
string decode[N];
int adj[N][N];

bool Read() {
  memset(adj, 0, sizeof adj);
  encode.clear();
  int nc;
  cin >> nc;
  if (!nc || cin.eof())
    return 0;
  int ne, m, u, v;
  string r, s;
  n = 0;
  for (int i = 0; i < nc; i++) {
    int last = -1;
    cin >> ne;
    for (int j = 0; j < ne; j++) {
      cin >> s;
      if (!encode.count(s)) {
        encode[s] = u = n;
        decode[u] = s;
        n++;
      }
      else
        u = encode[s];
      if (last > -1)
        adj[last][u] = 1;
      last = u;
    }
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> r >> s;
    u = encode[r];
    v = encode[s];
    adj[u][v] = 1;
  }

  return 1;
}

void Process() {
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        adj[i][j] |= (adj[i][k] & adj[k][j]);
  vii ans;
  int ans_ct = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (!adj[i][j] && !adj[j][i]) {
        ans_ct++;
        if (ans_ct < 3) 
          ans.push_back({ i, j });
      }
  cout << "Case " << ++ct << ", ";
  if (ans_ct)
    cout << ans_ct;
  else
    cout << "no";
  cout << " concurrent events";
  if (ans_ct) {
    cout << ":\n";
    for (ii x : ans) 
      cout << "(" << decode[x.first] << "," << decode[x.second] << ") ";
  }
  else
    cout << ".";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}