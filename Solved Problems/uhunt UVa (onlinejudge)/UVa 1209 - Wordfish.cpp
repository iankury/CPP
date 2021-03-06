#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;

struct Mirror_Char {
  char c;
  bool operator < (const Mirror_Char& mc) const {
    return c > mc.c;
  }
};

string Mirror_Print(const vector<Mirror_Char>& v) {
  string ans;
  for (int i = 0; i < v.size(); i++)
    ans.push_back(v[i].c);
  return ans;
}

int main() {
  FASTIO();

  while (1) {
    if (!(cin >> s)) break;
    int offset = 0;
    string ordered = s;
    sort(ordered.begin(), ordered.end());
    vector<Mirror_Char> mirror_string;
    vector<string> candidates;
    for (int i = 0; i < s.length(); i++)
      mirror_string.push_back(Mirror_Char{ s[i] });
    vector<Mirror_Char> temp = mirror_string;
    sort(temp.begin(), temp.end());
    string rev_ordered = Mirror_Print(temp);
    for (int i = 0; i < 10; i++) {
      next_permutation(mirror_string.begin(), mirror_string.end());
      candidates.push_back(Mirror_Print(mirror_string));
      if (candidates[candidates.size() - 1] == ordered) 
        offset = i;
    }
    if (s == ordered)
      offset = 10;
    sort(candidates.begin(), candidates.end());
    for (int i = 0; i < 11; i++) {
      candidates.push_back(s);
      if (s == rev_ordered) break;
      next_permutation(s.begin(), s.end());
    }
    string ans;
    int max_d = 0, min_d;
    for (int k = offset; k < candidates.size(); k++) {
      min_d = BIG;
      for (int i = 0; i < candidates[k].length(); i++)
        for (int j = i - 1; j < i + 2; j += 2)
          if (j >= 0 && j < candidates[k].length())
            min_d = min(min_d, abs(candidates[k][i] - candidates[k][j]));
      if (min_d > max_d) {
        ans = candidates[k];
        max_d = min_d;
      }
    }
    cout << ans << max_d << "\n";
    if (cin.eof()) break;
  }

  return 0;
}