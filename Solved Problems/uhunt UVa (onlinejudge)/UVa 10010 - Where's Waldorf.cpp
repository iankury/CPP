#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 55, M = 1000000007, BIG = 0x3f3f3f3f;

int n, m, k, ct = 0;
char a[N][N];
string s;
int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void Clear_Borders() {
  memset(a[0], 0, sizeof a[0]);
  memset(a[n + 1], 0, sizeof a[n + 1]);
  for (int i = 0; i < n + 3; i++)
    a[i][0] = a[i][m + 1] = 0;
}

bool Read() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      a[i][j] = toupper(a[i][j]);
    }
  cin >> k;

  return 1;
}

bool Rec(int idx, int i, int j, int dir) {
  if (!a[i][j])
    return 0;
  if (idx == s.length() - 1)
    return a[i][j] == s[idx];
  if (a[i][j] != s[idx])
    return 0;
  return Rec(idx + 1, i + dr[dir], j + dc[dir], dir);
}

void Process() {
  if (ct++)
    cout << "\n";
  for (int w = 0; w < k; w++) {
    cin >> s;
    for (int i = 0; i < s.length(); i++)
      s[i] = toupper(s[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        for (int dir = 0; dir < 8; dir++) 
          if (Rec(0, i, j, dir)) {
            cout << i << " " << j << "\n";
            goto DONE;
          }
  DONE: {}
  }
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}