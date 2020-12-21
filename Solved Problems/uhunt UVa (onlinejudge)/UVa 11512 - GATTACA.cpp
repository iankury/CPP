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
  vi RA, RA2, SA2, LCP, PLCP, Phi, next_sep;
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
    s[n - 1] = -128;
    int i, k, r;
    for (i = 0; i < n; i++) {
      SA[i] = i;
      RA[i] = s[i] + 128;
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
  int Lower_Bound(const string& pat) {
    int p = 0, q = n - 1, mid = p, res;
    while (p < q) {
      mid = p + (q - p) / 2;
      res = Pinha_Compare(pat, s.substr(SA[mid], pat.length()));
      if (res <= 0)
        q = mid;
      else
        p = mid + 1;
    }
    if (s.substr(SA[p], pat.length()) != pat)
      return -1;
    return p;
  }
  int Upper_Bound(const string& pat) {
    int p = 0, q = n - 1, mid = p, res;
    while (p < q) {
      mid = p + (q - p) / 2;
      res = Pinha_Compare(pat, s.substr(SA[mid], pat.length()));
      if (res < 0)
        q = mid;
      else
        p = mid + 1;
    }
    if (s.substr(SA[q], pat.length()) != pat)
      q--;
    return q;
  }
  int Pinha_Compare(const string& s1, const string& s2) {
    for (int i = 0; i < s1.length(); i++)
      if (s1[i] != s2[i])
        return s1[i] < s2[i] ? -1 : 1;
    return 0;
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
  Suffix_Array(const vector<string>& vs) { // For LCS of > 2 strings
    string s1 = vs[0];
    int total_sz = 0;
    for (int i = 0; i < vs.size(); i++)
      total_sz += 1 + vs[i].length();
    next_sep.resize(total_sz);
    char separator = -127;
    int j = 0;
    for (int i = 1; i < vs.size(); i++) {
      while (j <= s1.length())
        next_sep[j++] = s1.length();
      s1.push_back(separator++);
      s1.append(vs[i]);
    }
    while (j <= s1.length())
      next_sep[j++] = s1.length();
    Build_SA(s1, 1);
  }
  vi All_Occurrences(const string& pat) {
    vi ans;
    int LB = Lower_Bound(pat);
    if (LB < 0)
      return ans;
    int UB = Upper_Bound(pat);
    for (int i = LB; i <= UB; i++)
      ans.push_back(SA[i]);
    sort(begin(ans), end(ans));
    return ans;
  }
  set<string> LRS() {  // Longest Repeated Substrings  --  use needs_LCP = true
    set<string> ans;
    int i, maxLCP = -1;
    for (int i = 0; i < n; i++)
      maxLCP = max(maxLCP, LCP[i]);
    for (i = 1; i < n; i++)
      if (LCP[i] == maxLCP)
        ans.insert(s.substr(SA[i], maxLCP));
    return ans;
  }
  string LCS() { // Longest Common Substring (of TWO strings) -- use two-string constructor
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++) {
      if (((SA[i] < s1len) != (SA[i - 1] < s1len)) && LCP[i] > maxLCP)
        maxLCP = LCP[i], idx = SA[i];
    }
    return s.substr(idx, maxLCP);
  }
  set<string> All_LCS() { // Of TWO strings
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
  set<string> All_LCS_Of_Many(int n_of_str) { // Of at least n_of_str strings, n_of_str > 2
    set<string> ans;
    unordered_set<int> distinct;
    int i, maxLCP = 1, LB, UB;
    vi LCPsorted(n);
    for (int i = 0; i < n; i++)
      LCPsorted[i] = i;
    sort(begin(LCPsorted), end(LCPsorted), [this](int x1, int x2) {
      return LCP[x1] > LCP[x2];
      });
    for (int i : LCPsorted) {
      if (LCP[i] < maxLCP)
        break;
      distinct.clear();
      LB = Lower_Bound(s.substr(SA[i], LCP[i]));
      UB = Upper_Bound(s.substr(SA[i], LCP[i]));
      for (int j = LB; j <= UB; j++)
        distinct.insert(next_sep[SA[j]]);
      if (distinct.size() >= n_of_str) {
        maxLCP = LCP[i];
        ans.insert(s.substr(SA[i], maxLCP));
      }
    }
    return ans;
  }
};

string s;

bool Read() {
  cin >> s;


  return 1;
}

void Process() {
  Suffix_Array sa(s, 1);
  set<string> lrs = sa.LRS();
  string ans = *lrs.begin();
  if (ans.empty())
    cout << "No repetitions found!\n";
  else
    cout << ans << " " << sa.All_Occurrences(ans).size() << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}