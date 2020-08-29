#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 505;
int n, m, q;
ll d[N][N];

void Initialize_Floyd_Warshall() {
  memset(d, -1, sizeof d);
  for (int i = 0; i <= n; i++)
    d[i][i] = 0;
}

void Floyd_Warshall() {
  for (int k = 0; k <= n; k++)
    for (int i = 0; i <= n; i++)
      if (d[i][k] != -1)
        for (int j = 0; j <= n; j++)
          if (d[k][j] != -1)
            d[i][j] = d[i][j] == -1 ? d[i][k] + d[k][j] 
            : min(d[i][j], d[i][k] + d[k][j]);
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m >> q;
  Initialize_Floyd_Warshall();
  int u, v;
  ll w;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    d[u][v] = d[v][u] = d[u][v] == -1 ? w : min(d[u][v], w);
  }

  return 1;
}

void Process() {
  int u, v;
  Floyd_Warshall();
  for (int i = 0; i < q; i++) {
    cin >> u >> v;
    cout << d[u][v] << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}