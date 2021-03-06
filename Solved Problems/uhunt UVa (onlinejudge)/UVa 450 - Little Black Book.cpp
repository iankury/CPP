#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <sstream>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;
const string separator(40, '-');

bool Blank(const string& s) {
  if (s.empty()) return 1;
  for (char c : s)
    if (c != '\n' && !isblank(c))
      return 0;
  return 1;
}

struct Entry {
  string dept, title, fname, lname, address, hphone, wphone, mail;
  void Print() {
    cout << separator << "\n";
    cout << title << " " << fname << " " << lname << "\n";
    cout << address << "\n";
    cout << "Department: " << dept << "\n";
    cout << "Home Phone: " << hphone << "\n";
    cout << "Work Phone: " << wphone << "\n";
    cout << "Campus Box: " << mail << "\n";
  }
  bool operator < (const Entry& s) const {
    return lname < s.lname;
  }
};

vector<Entry> entries;

int main() {
  FASTIO();

  int n;
  cin >> n;
  string s, dept, title, fname, lname, address, hphone, wphone, mail;
  for (int i = 0; i < n; i++) {
    dept.clear();
    while (Blank(dept))
      getline(cin, dept);
    while (getline(cin, s)) {
      if (Blank(s)) break;
      stringstream ss(s);
      vector<string> tokens;
      while (getline(ss, s, ','))
        tokens.push_back(s);
      entries.push_back( { dept, tokens[0], tokens[1], tokens[2], 
        tokens[3], tokens[4], tokens[5], tokens[6] } );
      if (cin.eof()) break;
    }
  }
  sort(entries.begin(), entries.end());
  for (Entry x : entries)
    x.Print();

  return 0;
}