#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Trie {
  struct Node {
    bool word;
    unordered_map<char, Node*> ch;
    Node() : word(0) {}
  };
  Node* root;
  Trie() : root(new Node()) {}
  void Add(const string& s) {
    Node* p = root;
    for (char c : s) 
      p = p->ch.count(c) ? p->ch[c] : p->ch[c] = new Node();
    p->word = 1;
  }
  void Delete(const string& s) {
    vector<Node*> v;
    Node* p = root;
    for (char c : s) {
      if (!p->ch.count(c))
        return;
      v.push_back(p);
      p = p->ch[c];
    }
    p->word = 0;
    int idx = s.length() - 1;
    while (!v.empty() && p->ch.empty()) {
      v.back()->ch.erase(s[idx--]);
      delete p;
      p = v.back();
      v.pop_back();
    }
  }
  bool Word(const string& s) {
    Node* p = root;
    for (char c : s) {
      if (!p->ch.count(c)) 
        return 0;
      p = p->ch[c];
    }
    return p->word;
  }
  bool Prefix_Of_Longer_Word(const string& s) {
    Node* p = root;
    for (char c : s) {
      if (!p->ch.count(c))
        return 0;
      p = p->ch[c];
    }
    return !p->ch.empty();
  }
};

int main() {
  FASTIO();

  return 0;
}