#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int KMP(const string& text, int st_idx, const string& pat) {
  vi pi(pat.length() + 1);
  pi[0] = 0;
  int k = 0;
  for (int q = 1; q < pat.length(); q++) {
    while (k > 0 && pat[k] != pat[q])
      k = pi[k];
    if (pat[k] == pat[q])
      k++;
    pi[q] = k;
  }
  int q = 0;
  for (int i = st_idx; i < text.length(); i++) {
    while (q > 0 && pat[q] != text[i])
      q = pi[q - 1];
    if (pat[q] == text[i])
      q++;
    if (q == pat.length())
      return 1 + i - pat.length();
  }
  return -1;
}

int n;
vector<string> dict;
string text;

int Number_Of_Occurrences(int st_idx, vi pending) {
  int mn = BIG, sel = 0, ans = 0, kmp, en;
  vi next_pending;
  for (int i : pending) {
    kmp = KMP(text, st_idx, dict[i]);
    if (kmp < 0)
      continue;
    next_pending.push_back(i);
    en = kmp + dict[i].length();
    if (en < mn) {
      mn = en;
      sel = i;
    }
  }
  if (!next_pending.empty())
    ans += 1 + Number_Of_Occurrences(mn, next_pending);
  return ans;
}

bool Read() {
  string s;
  while (getline(cin, s)) {
    if (s.find_first_of('#') != string::npos)
      break;
    dict.push_back(s);
  }
  getline(cin, text);
  return 1;
}

char Next(char c) {
  if (c == ' ')
    return 'A';
  if (c == 'Z')
    return ' ';
  return c + 1;
}

void Print(const string& s) {
  stringstream ss(s);
  string t;
  int len = 0;
  while (ss >> t) {
    if (len == 0) {
      cout << t;
      len = t.length();
    }
    else {
      if (++len + t.length() > 60) {
        cout << "\n" << t;
        len = t.length();
      }
      else {
        cout << " " << t;
        len += t.length();
      }
    }
  }
  cout << "\n";
}

void Process() {
  string ans;
  int mx = -1, occ;
  vi xx(dict.size());
  for (int i = 0; i < dict.size(); i++)
    xx[i] = i;
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < text.length(); j++)
      text[j] = Next(text[j]);
    occ = Number_Of_Occurrences(0, xx);
    if (occ > mx) {
      mx = occ;
      ans = text;
    }
  }
  Print(ans);
}

int main() {
  FASTIO();

  Read();
  Process();

  return 0;
}