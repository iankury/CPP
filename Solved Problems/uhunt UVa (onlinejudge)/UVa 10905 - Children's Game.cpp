#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 55, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
string a[N];

struct Node {
  string s;
  Node* p;
  Node(const string& _s) : p(0), s(_s) {}
};

struct List {
  Node* root, *back;
  void Push_Root(const string& s) {
    root = new Node(s);
    back = root;
  }
  void Push(const string& s) {
    Node* p = new Node(s);
    back->p = p;
    back = p;
  }
  List() {
    Push_Root(a[0]);
    for (int i = 1; i < n; i++)
      Push(a[i]);
  }
  Node* At(int idx) {
    Node* p = root;
    while (idx--)
      p = p->p;
    return p;
  }
  void Swap_With_Predecessor(int i) {
    if (i == 1) {
      Node* old_root = root;
      root = root->p;
      old_root->p = root->p;
      root->p = old_root;
    }
    else {
      Node* u = At(i - 2);
      Node* v = u->p;
      u->p = v->p;
      v->p = u->p->p;
      u->p->p = v;
    }
  }
  void Print() {
    Node* p = root;
    while (p) {
      cout << p->s;
      p = p->p;
    }
    cout << "\n";
  }
  bool operator > (const List& list) const {
    int i = 0, j = 0;
    Node* p = root, *q = list.root;
    while (1) {
      if (i >= p->s.length()) {
        p = p->p;
        if (!p)
          return 0;
        i = 0;
      }
      if (j >= q->s.length()) {
        q = q->p;
        if (!q)
          return 0;
        j = 0;
      }
      if (p->s[i] > q->s[j]) 
        return 1;
      else if (p->s[i] < q->s[j])
        return 0;
      ++i;
      ++j;
    }
    return 0;
  }
};

bool Read() {
  cin >> n;
  if (cin.eof() || !n)
    return 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  return 1;
}

void Process() {
  List r, s;
  bool done = 0;
  int start_from = 1;
  while (!done) {
    done = 1;
    for (int i = start_from; i < n; i++) {
      s.Swap_With_Predecessor(i);
      if (s > r) {
        r.Swap_With_Predecessor(i);
        done = 0;
        start_from = max(1, start_from - 1);
        break;
      }
      else {
        s.Swap_With_Predecessor(i);
        start_from++;
      }
    }
  }
  r.Print();
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}