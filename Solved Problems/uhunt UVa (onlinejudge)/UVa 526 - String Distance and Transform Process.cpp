#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Levenshtein {
  enum { MATCH, ADD, DELETE, CHANGE };
  struct Operation {
    int type;
    int cb, ca;
  };
  const string& a, b;
  int distance;
  vector<vi> dp;
  vector<Operation> path;
  void Bottom_Up() {
    for (int i = 0; i <= a.length(); i++)
      dp[0][i] = i;
    for (int i = 0; i <= b.length(); i++)
      dp[i][0] = i;
    for (int i = 1; i <= b.length(); i++)
      for (int j = 1; j <= a.length(); j++)
        dp[i][j] = b[i - 1] == a[j - 1] ? dp[i - 1][j - 1]
        : 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
    distance = dp[b.length()][a.length()];
  }
  void Build_Path() {
    int i = b.length(), j = a.length();
    while (i > 0 || j > 0) {
      if (i == 0)
        path.push_back({ DELETE, i, --j });
      else if (j == 0)
        path.push_back({ ADD, --i, j });
      else {
        int mn = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
        if (mn == dp[i - 1][j - 1]) {
          if (dp[i - 1][j - 1] == dp[i][j])
            path.push_back({ MATCH, --i, --j });
          else
            path.push_back({ CHANGE, --i, --j });
        }
        else if (mn == dp[i - 1][j])
          path.push_back({ ADD, --i, j });
        else
          path.push_back({ DELETE, i, --j });
      }
    }
    reverse(begin(path), end(path));
  }
  Levenshtein(const string& a, const string& b) : a(a), b(b) {
    dp.assign(b.length() + 1, vi(a.length() + 1));
    Bottom_Up();
    Build_Path();
  }
  void Print_Path() {
    int op_n = 0;
    int offset = 1;
    for (const Operation& o : path) {
      if (o.type != MATCH)
        cout << ++op_n << " ";
      if (o.type == ADD) {
        cout << "Insert " << o.ca + offset << "," << b[o.cb] << "\n";
        offset++;
      }
      else if (o.type == DELETE) {
        cout << "Delete " << o.ca + offset << "\n";
        offset--;
      }
      else if (o.type == CHANGE)
        cout << "Replace " << o.ca + offset << "," << b[o.cb] << "\n";
    }
  }
};

int main() {
  FASTIO();

  string r, s;
  int ct = 0;
  while (getline(cin, r)) {
    if (!getline(cin, s))
      break;
    if (ct++)
      cout << "\n";
    Levenshtein lev(r, s);
    cout << lev.distance << "\n";
    lev.Print_Path();

    if (cin.eof())
      break;
  }

  return 0;
}