#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, q;
vector<vi> a;
vector<vector<ll>> psm;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  cin >> q;
  a.assign(n + 1, vi(n + 1));
  char c;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      cin >> c;
      a[i][j] = (c == '*');
    }

  return 1;
}

void Process() {
  psm.assign(n + 1, vector<ll>(n + 1, 0));
  psm[1][1] = a[1][1];
  for (int i = 2; i <= n; i++) {
    psm[1][i] = psm[1][i - 1] + a[1][i];
    psm[i][1] = psm[i - 1][1] + a[i][1];
  }
  for (int i = 2; i <= n; i++)
    for (int j = 2; j <= n; j++) 
      psm[i][j] = psm[i - 1][j] + psm[i][j - 1] - psm[i - 1][j - 1] + a[i][j];
  int smi, smj, lari, larj;
  for (int i = 0; i < q; i++) {
    cin >> smi >> smj >> lari >> larj;
    if (smi > lari)
      swap(smi, lari);
    if (smj > larj)
      swap(smj, larj);
    cout << psm[lari][larj] + psm[smi - 1][smj - 1] 
      - psm[smi - 1][larj] - psm[lari][smj - 1] << "\n";
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}