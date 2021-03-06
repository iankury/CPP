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

const int N = 21, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, m, rich, poor;
char a[N][N];

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> m >> rich >> poor;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];

  return 1;
}

void Process() {
  cout << "Case " << ++ct << ": ";
  int freq[26];
  memset(freq, 0, sizeof freq);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      freq[a[i][j] - 'A']++;
  sort(freq, freq + 26, greater<int>());
  int ans = freq[0] * rich;
  for (int i = 1; i < 26 && freq[i]; i++) 
    ans += freq[i] * (freq[i] == freq[0] ? rich : poor);
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (Read() && T--)
    Process();

  return 0;
}