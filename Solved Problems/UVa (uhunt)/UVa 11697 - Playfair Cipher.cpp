#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
string s, key;
char D[300], R[300], row[300], col[300];
char a[30][30];

bool Read() {
  getline(cin, key);
  getline(cin, s);

  return 1;
}

string Encode(char p, char q) {
  if (row[p] == row[q])
    return string{ R[p], R[q] };
  else if (col[p] == col[q])
    return string{ D[p], D[q] };
  return string{ a[row[p]][col[q]], a[row[q]][col[p]] };
}

char FirstAv(const vector<bool>& vis) {
  for (int i = 0; i < vis.size(); i++)
    if (!vis[i])
      return i + 'a';
  return 0;
}

void Process() {
  reverse(begin(key), end(key));
  vector<bool> vis(26, 0);
  vis['q' - 'a'] = 1;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) {
      if (!key.empty()) {
        while (!key.empty() && (!isalpha(key.back()) || vis[key.back() - 'a']))
          key.pop_back();
        if (key.empty() || vis[key.back() - 'a'])
          a[i][j] = FirstAv(vis);
        else 
          a[i][j] = key.back();
        if (!key.empty())
          key.pop_back();
      }
      else
        a[i][j] = FirstAv(vis);
      vis[a[i][j] - 'a'] = 1;
    }
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) {
      D[a[i][j]] = a[(i + 1) % 5][j];
      R[a[i][j]] = a[i][(j + 1) % 5];
      row[a[i][j]] = i;
      col[a[i][j]] = j;
    }
  string ans, t;
  while (!s.empty()) {
    if (isalpha(s.back()))
      t.push_back(s.back());
    s.pop_back();
  }
  while (t.length() > 1) {
    char c = t.back();
    t.pop_back();
    if (t.back() == c)
      ans.append(Encode(c, 'x'));
    else {
      ans.append(Encode(c, t.back()));
      t.pop_back();
    }
  }
  if (!t.empty())
    ans.append(Encode(t.back(), 'x'));
  for (int i = 0; i < ans.length(); i++)
    ans[i] = toupper(ans[i]);
  cout << ans << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  getline(cin, s);
  while (T-- && Read())
    Process();

  return 0;
}