#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

int n, k;
vector<string> a;
vector<vi> psa_rows, psa_cols, psa_score_r, psa_score_c;
vector<vi> score_rows, score_cols;

int Range_Query(const vector<vi>& psa, int rc, int i, int j) {
  if (i >= n)
    return 0;
  return psa[rc][j] - (i ? psa[rc][i - 1] : 0);
}

void Initialize_PSA() {
  psa_rows.assign(n, vi(n));
  psa_cols.assign(n, vi(n));

  for (int r = 0; r < n; r++) {
    psa_rows[r][0] = (a[r][0] == 'W');
    for (int j = 1; j < n; j++)
      psa_rows[r][j] = int(a[r][j] == 'W') + psa_rows[r][j - 1];
  }
  
  for (int c = 0; c < n; c++) {
    psa_cols[c][0] = (a[0][c] == 'W');
    for (int i = 1; i < n; i++)
      psa_cols[c][i] = int(a[i][c] == 'W') + psa_cols[c][i - 1];
  }
}

void Initialize_PSA_Scores() {
  psa_score_r.assign(n, vi(n));
  for (int c = 0; c < n; c++) {
    psa_score_r[c][0] = score_rows[0][c];
    for (int i = 1; i < n; i++)
      psa_score_r[c][i] = score_rows[i][c] + psa_score_r[c][i - 1];
  }

  psa_score_c.assign(n, vi(n));
  for (int r = 0; r < n; r++) {
    psa_score_c[r][0] = score_cols[r][0];
    for (int j = 1; j < n; j++)
      psa_score_c[r][j] = score_cols[r][j] + psa_score_c[r][j - 1];
  }
}

void Solve() {
  Initialize_PSA();
  
  score_rows.assign(n, vi(n));
  score_cols.assign(n, vi(n));
 
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      score_rows[i][j] = (
        (j == 0 || Range_Query(psa_rows, i, 0, j - 1) == j) &&
        (j + k == n || (j + k < n 
          && Range_Query(psa_rows, i, j + k, n - 1) == n - j - k))
      );
      score_cols[i][j] = (
        (i == 0 || Range_Query(psa_cols, j, 0, i - 1) == i) &&
        (i + k == n || (i + k < n && 
          Range_Query(psa_cols, j, i + k, n - 1) == n - i - k))
      );
    }
  
  Initialize_PSA_Scores();
  
  vector<bool> row_complete(n), col_complete(n);
  
  for (int i = 0; i < n; i++)
    if (Range_Query(psa_rows, i, 0, n - 1) == n)
      row_complete[i] = 1;
  for (int j = 0; j < n; j++)
    if (Range_Query(psa_cols, j, 0, n - 1) == n)
      col_complete[j] = 1;

  vi psa_complete_rows(n), psa_complete_cols(n);
  psa_complete_rows[0] = row_complete[0];
  psa_complete_cols[0] = col_complete[0];
  for (int i = 1; i < n; i++) {
    psa_complete_rows[i] = psa_complete_rows[i - 1] + int(row_complete[i]);
    psa_complete_cols[i] = psa_complete_cols[i - 1] + int(col_complete[i]);
  }
  
  int ans = 0;

  for (int i = 0; i <= n - k; i++) 
    for (int j = 0; j <= n - k; j++) {
      const int cur = (
        Range_Query(psa_score_r, j, i, i + k - 1) +
        Range_Query(psa_score_c, i, j, j + k - 1) +
        psa_complete_rows[n - 1] - 
        psa_complete_rows[i + k - 1] +
        (i ? psa_complete_rows[i - 1] : 0) +
        psa_complete_cols[n - 1] - 
        psa_complete_cols[j + k - 1] +
        (j ? psa_complete_cols[j - 1] : 0)
      );
      ans = max(ans, cur);
    }

  cout << ans << "\n";
}

int main() {
  io();

  while (cin >> n) {
    cin >> k;
    a.resize(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    Solve();
  }

  return 0;
}