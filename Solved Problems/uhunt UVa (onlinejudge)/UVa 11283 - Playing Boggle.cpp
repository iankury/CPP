#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, ct = 0;
char a[6][6];
bool vis[66];
int points[20];
int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
string s;

bool Read() {
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 4; j++)
      cin >> a[i][j];
  cin >> n;

  return 1;
}

bool Rec(int idx, int i, int j) {
  if (!a[i][j] || vis[i * 10 + j] || a[i][j] != s[idx])
    return 0;
  if (idx == s.length() - 1)
    return 1;
  vis[i * 10 + j] = 1;
  for (int k = 0; k < 8; k++)
    if (Rec(idx + 1, i + dr[k], j + dc[k])) {
      vis[i * 10 + j] = 0;
      return 1;
    }
  vis[i * 10 + j] = 0;
  return 0;
}

bool Found() {
  for (int i = 1; i < 5; i++)
    for (int j = 1; j < 5; j++)
      if (Rec(0, i, j))
        return 1;
  return 0;
}

void Process() {
  cout << "Score for Boggle game #" << ++ct << ": ";
  int ans = 0;
  while (n--) {
    cin >> s;
    if (Found())
      ans += points[s.length()];
  }
  cout << ans << "\n";
}

int main() {
  FASTIO();

  memset(a, 0, sizeof a);
  memset(vis, 0, sizeof vis);
  points[0] = points[1] = points[2] = 0;
  points[3] = points[4] = 1;
  points[5] = 2;
  points[6] = 3;
  points[7] = 5;
  for (int i = 8; i < 20; i++)
    points[i] = 11;

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}