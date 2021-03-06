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

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, incoming[N];
vi adj[N], ts;
priority_queue<int, vi, greater<int>> Q;
map<string, int> drink_to_num;
string num_to_drink[N];

bool Read() {
  drink_to_num.clear();
  for (int i = 0; i < N; i++)
    adj[i].clear();
  memset(incoming, 0, sizeof incoming);
  cin >> n;
  if (cin.eof()) return 0;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    num_to_drink[i] = s;
    if (drink_to_num.count(s)) 
      continue;
    drink_to_num[s] = i;
  }
  cin >> m;
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> s;
    u = drink_to_num[s];
    cin >> s;
    v = drink_to_num[s];
    adj[u].push_back(v);
    incoming[v]++;
  }

  return 1;
}

void Process() {
  ts.clear();
  for (auto& drink : drink_to_num) {
    if (!incoming[drink.second])
      Q.push(drink.second);
  }
  while (!Q.empty()) {
    int u = Q.top();
    Q.pop();
    ts.push_back(u);
    for (int v : adj[u])
      if (--incoming[v] == 0)
        Q.push(v);
  }
  cout << "Case #" << ++ct << ": Dilbert should drink beverages in this order:";
  for (int u : ts)
    cout << " " << num_to_drink[u];
  cout << ".\n\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}