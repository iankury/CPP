#include <bits/stdc++.h>
using namespace std;

const int M = 1000000007;

struct Mint {
  int x;
  Mint(int _value = 0) : x(_value) {}
  operator int() { return x; }
  Mint operator + (const Mint& _a) const { int ans = x + _a.x; return ans - (ans >= M) * M; }
  Mint& operator += (const Mint& _a) { *this = *this + _a; return *this; }
  istream& operator >> (istream& is) { is >> this->x; return is; }
  ostream& operator << (ostream& os) const { os << this->x; return os; }
};

struct Trie {
  struct Node {
    bool word = 0;
    unordered_map<char, Node*> ch;
  };
  Node* root = new Node;
  void Add(const string& s) {
    Node* p = root;
    for (char c : s)
      p = p->ch.count(c) ? p->ch[c] : p->ch[c] = new Node();
    p->word = 1;
  }
};

string s;
int k;
vector<string> a;

Mint Process() {
  int n = s.length();
  s = "0" + s;

  vector<Mint> dp(n + 1, 0);
  dp[0] = 1;

  Trie trie;
  for (const auto& x : a)
    trie.Add(x);

  Trie::Node* p;
  char c;
  for (int i = 0; i < n; i++) {
    if (dp[i].x == 0)
      continue;
    p = trie.root;
    for (int j = i + 1; j <= n; j++) {
      c = s[j];
      if (!p->ch.count(c))
        break;
      p = p->ch[c];
      if (p->word) 
        dp[j] += dp[i];
    }
  }
  
  return dp[n];
}

void Output() { cout << Process() << "\n"; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  while (cin >> s) {
    cin >> k;
    a.resize(k);
    for (int i = 0; i < k; i++)
      cin >> a[i];

    Output();
  }

  return 0;
}