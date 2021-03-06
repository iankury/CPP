#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, S = 12, BIG = 0x3f3f3f3f;

int ct = 0;
int g, n, s, k[S], a[N][N], p[S][N], score[N];

bool Read() {
  cin >> g >> n;
  if (!g && !n) return 0;
  for (int i = 1; i <= g; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  cin >> s; 
  for (int i = 1; i <= s; i++) {
    cin >> k[i];
    for (int j = 1; j <= k[i]; j++)
      cin >> p[i][j];
  }

  return 1;
}

void Process() {
  for (int ix = 1; ix <= s; ix++) {
    memset(score, 0, sizeof score);
    int mx = 0;
    for (int i = 1; i <= g; i++)
      for (int j = 1; j <= n; j++)
        if (a[i][j] <= k[ix]) {
          score[j] += p[ix][a[i][j]];
          if (score[j] > mx)
            mx = score[j];
        }
    bool started = 0;
    for (int i = 1; i <= n; i++)
      if (score[i] == mx) {
        if (started) cout << " ";
        cout << i;
        started = 1;
      }
    cout << "\n";
  }
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}