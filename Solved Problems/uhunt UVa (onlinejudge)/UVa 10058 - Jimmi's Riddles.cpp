#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;
const unordered_set<string> nouns = { "tom", "jerry",
  "goofy", "mickey", "jimmy", "dog", "cat", "mouse" };

bool Verb(string p) {
  if (p.back() == 's')
    p.pop_back();
  return p == "hate" || p == "love" || p == "know" || p == "like";
}

bool Noun(const string& p) { return nouns.count(p);  }

bool Article(const string& p) { return p == "a" || p == "the"; }

bool Active_List(vector<string> w) {
  if (!Noun(w.back()))
    return 0;
  w.pop_back();
  if (w.empty())
    return 1;
  if (w.back() != "and") {
    if (!Article(w.back()))
      return 0;
    w.pop_back();
    if (w.empty())
      return 1;
    if (w.back() != "and")
      return 0;
  }
  w.pop_back();
  return Active_List(w);
}

bool Action(const vector<string>& w) {
  int verb_idx = -1;
  for (int i = 0; i < w.size(); i++) 
    if (Verb(w[i])) {
      if (verb_idx == -1)
        verb_idx = i;
      else
        return 0;
    }
  if (verb_idx <= 0 || verb_idx == w.size() - 1)
    return 0;
  vector<string> al1, al2;
  for (int i = 0; i < verb_idx; i++)
    al1.push_back(w[i]);
  for (int i = verb_idx + 1; i < w.size(); i++)
    al2.push_back(w[i]);
  return Active_List(al1) && Active_List(al2);
}

bool Statement(vector<string> w) {
  if (w.empty())
    return 0;
  int idx = w.size() - 1;
  for (; idx >= 0; idx--)
    if (w[idx] == ",")
      break;
  if (idx < 0)
    return Action(w);
  vector<string> tail;
  for (int i = idx + 1; i < w.size(); i++)
    tail.push_back(w[i]);
  if (!Action(tail))
    return 0;
  while (w.back() != ",")
    w.pop_back();
  w.pop_back();
  return Statement(w);
}

void Process() {
  vector<string> w;
  stringstream ss(s);
  while (ss >> s) {
    if (s != ",") {
      int idx = s.find_first_of(',');
      if (idx != string::npos) {
        if (idx == s.find_last_of(',')) {
          string s1 = "$";
          if (idx > 0)
            s1 = s.substr(0, idx);
          string s2 = "$";
          if (idx < s.length() - 1)
            s2 = s.substr(idx + 1);
          if (s1 != "$")
            w.push_back(s1);
          w.push_back(",");
          s = s2;
        }
      }
    }
    if (s != "$")
      w.push_back(s);
  }
  if (Statement(w))
    cout << "YES I WILL\n";
  else
    cout << "NO I WON'T\n";
}

int main() {
  FASTIO();

  while (getline(cin, s)) {
    Process();
    if (cin.eof())
      break;
  }

  return 0;
}