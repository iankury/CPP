#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

class Suffix_Array {
  string s;
  int n, s1len, s2len;
  vi RA, RA2, SA2, LCP, PLCP, Phi;
  void Sort(int k) {
    int max_rank = max(256, n);
    int* freq = new int[max_rank];
    memset(freq, 0, max_rank << 2);
    for (int i = 0; i < n; i++)
      freq[i + k < n ? RA[i + k] : 0]++;
    int t, sum = 0;
    for (int i = 0; i < max_rank; i++) {
      t = freq[i];
      freq[i] = sum;
      sum += t;
    }
    for (int i = 0; i < n; i++)
      SA2[freq[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (int i = 0; i < n; i++)
      SA[i] = SA2[i];
    delete freq;
  }
  void Build_LCP() { // Longest Common Prefix
    Phi.resize(n); LCP.resize(n); PLCP.resize(n);
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
      Phi[SA[i]] = SA[i - 1];
    for (i = L = 0; i < n; i++) {
      if (Phi[i] == -1) {
        PLCP[i] = 0;
        continue;
      }
      while (s[i + L] == s[Phi[i] + L])
        L++;
      PLCP[i] = L;
      L = max(L - 1, 0);
    }
    for (i = 0; i < n; i++)
      LCP[i] = PLCP[SA[i]];
  }
  void Build_SA(const string& _s, bool needs_LCP) {
    n = _s.length() + 1;
    s.resize(n); RA.resize(n); RA2.resize(n); SA.resize(n); SA2.resize(n);
    _s.copy(&s[0], _s.length(), 0);
    s[n - 1] = '$';
    int i, k, r;
    for (i = 0; i < n; i++) {
      SA[i] = i;
      RA[i] = s[i];
    }
    for (k = 1; k < n; k <<= 1) {
      Sort(k);
      Sort(0);
      RA2[SA[0]] = r = 0;
      for (i = 1; i < n; i++)
        RA2[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] &&
          RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
      for (i = 0; i < n; i++)
        RA[i] = RA2[i];
      if (RA[SA[n - 1]] == n - 1)
        break;
    }
    if (needs_LCP)
      Build_LCP();
  }
public:
  vi SA;
  Suffix_Array(const string& _s, bool needs_LCP = 0) { Build_SA(_s, needs_LCP); }
  Suffix_Array(const string& s1, const string& s2) { // For LCS
    string s3;
    s1len = s1.length();
    s2len = s2.length();
    s3.resize(s1len + s2len + 1);
    s3[s1len] = 0;
    s1.copy(&s3[0], s1len, 0);
    s2.copy(&s3[s1len + 1], s2len, 0);
    Build_SA(s3, 1);
  }
  vi All_Occurrences(const string& pat) {
    vi ans;
    int p = 0, p_backup = 0, q = n - 1, mid = p, m = pat.length();
    while (p < q) {
      mid = p + (q - p) / 2;
      int res = s.substr(SA[mid], m).compare(pat);
      if (res >= 0)
        q = mid;
      else
        p = mid + 1;
    }
    if (s.substr(SA[p], m) != pat)
      return ans;
    p_backup = p; p = 0; q = n - 1; mid = p;
    while (p < q) {
      mid = p + (q - p) / 2;
      int res = s.substr(SA[mid], m).compare(pat);
      if (res > 0)
        q = mid;
      else
        p = mid + 1;
    }
    if (s.substr(SA[q], m) != pat)
      q--;
    for (int i = p_backup; i <= q; i++)
      ans.push_back(SA[i]);
    sort(begin(ans), end(ans));
    return ans;
  }
  string LRS() {  // Longest Repeated Substring  --  use needs_LCP = true
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++)
      if (LCP[i] > maxLCP)
        maxLCP = LCP[i], idx = i;
    return s.substr(idx, maxLCP);
  }
  string LCS() { // Longest Common Substring  --  use two-string constructor
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++) {
      if (((SA[i] < s1len) != (SA[i - 1] < s1len)) && LCP[i] > maxLCP)
        maxLCP = LCP[i], idx = SA[i];
    }
    return s.substr(idx, maxLCP);
  }
  set<string> All_LCS() {
    set<string> ans;
    vi idc;
    int i, maxLCP = 1;
    for (i = 1; i < n; i++) {
      if ((SA[i] < s1len) != (SA[i - 1] < s1len)) {
        if (LCP[i] == maxLCP)
          idc.push_back(SA[i]);
        else if (LCP[i] > maxLCP) {
          idc.clear();
          idc.push_back(SA[i]);
          maxLCP = LCP[i];
        }
      }
    }
    for (int x : idc)
      ans.insert(s.substr(x, maxLCP));
    return ans;
  }
};

int main() {
  FASTIO();

  string r, s;
  int ct = 0;
  while (cin >> r) {
    if (cin.eof())
      break;
    if (ct++)
      cout << "\n";
    cin >> s;
    Suffix_Array sa(r, s);
    set<string> ans = sa.All_LCS();
    if (ans.empty())
      cout << "No common sequence.\n";
    else
      for (const string& x : sa.All_LCS())
        cout << x << "\n";
  }

  return 0;
}