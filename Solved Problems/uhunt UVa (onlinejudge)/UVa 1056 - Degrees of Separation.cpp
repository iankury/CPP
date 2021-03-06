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

const int N = 55, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, d[N][N];
map<string, int> encode;
vector<string> decode;

int Encode(const string& s) {
  if (!encode.count(s)) {
    encode[s] = decode.size();
    decode.push_back(s);
  }
  return encode[s];
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m;
  if (!n && !m)
    return 0;
  encode.clear();
  decode.clear();
  memset(d, BIG, sizeof d);
  int u, v;
  string r, s;
  for (int i = 0; i < m; i++) {
    cin >> r >> s;
    u = Encode(r);
    v = Encode(s);
    d[u][v] = d[v][u] = 1;
  }

  return 1;
}

void Process() {
  for (int i = 0; i < n; i++)
    d[i][i] = 1;
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  int ans = -1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      ans = max(ans, d[i][j]);
  cout << "Network " << ++ct << ": ";
  if (ans >= BIG)
    cout << "DISCONNECTED";
  else
    cout << ans;
  cout << "\n\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}