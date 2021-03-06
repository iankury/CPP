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

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

enum { SORT_BY_KEY, SORT_BY_R };
int ct = 0;
int n, m, s, t, n_monkeys, parallel_drinks;
int MONKEY_SORT_MODE;
vi level, st_from;

template <typename T> struct Node {
  T x;
  Node* prev, *next;
};

template <typename T> struct List {
  Node<T>* front, *back;
  int sz;
  void Push_Front(const T& _data) {
    if (!sz) {
      Node<T>* p = new Node<T>{ _data, 0, 0 };
      front = back = p;
    }
    else {
      Node<T>* p = new Node<T>{ _data, 0, front };
      front->prev = p;
      front = p;
    }
    sz++;
  }
  void Push_Back(const T& _data) {
    if (!sz) {
      Node<T>* p = new Node<T>{ _data, 0, 0 };
      front = back = p;
    }
    else {
      Node<T>* p = new Node<T>{ _data, back, 0 };
      back->next = p;
      back = p;
    }
    sz++;
  }
  void Pop_Front() {
    if (sz) {
      if (sz == 1) {
        delete front;
        front = back = 0;
      }
      else {
        Node<T>* todel = front;
        front = front->next;
        front->prev = 0;
        delete todel;
      }
      sz--;
    }
  }
  void Pop_Back() {
    if (sz) {
      if (sz == 1) {
        delete back;
        front = back = 0;
      }
      else {
        Node<T>* todel = back;
        back = back->prev;
        back->next = 0;
        delete todel;
      }
      sz--;
    }
  }
  T& Front() {
    return front->x;
  }
  T& Back() {
    return back->x;
  }
  void Erase(Node<T>* p) {
    if (p) {
      if (p == front)
        Pop_Front();
      else if (p == back)
        Pop_Back();
      else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        sz--;
      }
    }
  }
  bool Empty() { return !sz; }
  List() : sz(0), front(0), back(0) {}
  List(const T& _node) : sz(0) {
    Push_Back(_node);
  }
  List(const vector<T>& _v) {
    for (const T& _node : _v)
      Push_Back(_node);
  }
  ~List() {
    Node<T>* p = front;
    while (p) {
      Node<T>* todel = p;
      p = p->next;
      delete todel;
    }
  }
};

struct Seg { // Attention: interval is [L,R)
  int L, R;
  int Len() {
    return R - L;
  }
  operator bool() const {
    return L < R;
  }
  bool operator == (const Seg& p) const {
    return L == p.L && R == p.R;
  }
};
vector<Seg> segs;
vector<vector<List<Seg>>> threads;

Seg Intersection(const Seg& p, const Seg& q) {
  if (p.R <= q.L || q.R <= p.L)
    return { 0, 0 };
  if (p.L <= q.L && p.R >= q.R)
    return q;
  if (q.L <= p.L && q.R >= p.R)
    return p;
  if (p.R < q.R)
    return { q.L, p.R };
  return { p.L, q.R };
}

pair<Seg, Seg> Difference(const Seg& p, const Seg& q) {
  if (p.R <= q.L || q.R <= p.L)
    return { { 0, 0 }, { 0, 0 } };
  if (p.L <= q.L && p.R >= q.R)
    return { { p.L, q.L }, { q.R, p.R } };
  if (q.L <= p.L && q.R >= p.R)
    return { { q.L, p.L }, { p.R, q.R } };
  if (p.R < q.R)
    return { { p.L, q.L}, { p.R, q.R } };
  return { { q.L, p.L }, { q.R, p.R } };
}

struct Monkey : Seg {
  int key, need;
  vector<Seg> drinks;
  bool operator < (const Monkey& p) const {
    if (MONKEY_SORT_MODE == SORT_BY_KEY)
      return key < p.key;
    if (R == p.R) {
      if (need == p.need)
        return L > p.L;
      return need > p.need;
    }
    return R < p.R;
  }
};
vector<Monkey> monkeys;

struct Edge;
vector<vector<Edge>> adj;
struct Edge {
  int v, c, rsd;
  void Augment(int p) {
    c -= p;
    adj[v][rsd].c += p;
  }
};

void Add(int u, int v, int c) {
  adj[u].push_back({ v, c, (int)adj[v].size() });
  adj[v].push_back({ u, 0, (int)adj[u].size() - 1 });
}

int DFS(int u, int flow) {
  if (u == t)
    return flow;
  for (; st_from[u] < adj[u].size(); st_from[u]++) {
    Edge& edge = adj[u][st_from[u]];
    if (edge.c && level[edge.v] == 1 + level[u]) {
      int bn = DFS(edge.v, min(flow, edge.c));
      if (bn) {
        edge.Augment(bn);
        return bn;
      }
    }
  }
  return 0;
}

bool BFS() {
  level.assign(n + 1, -1);
  level[s] = 0;
  queue<int> Q;
  Q.push(s);
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    for (const Edge& edge : adj[u])
      if (edge.c && level[edge.v] == -1) {
        level[edge.v] = level[u] + 1;
        Q.push(edge.v);
      }
  }
  return level[t] != -1;
}

void Build_Segs() {
  List<Seg> buffer, toadd;
  for (const Monkey& monkey : monkeys)
    toadd.Push_Back(monkey);
  Seg cur, isect;
  pair<Seg, Seg> diff;
  while (!toadd.Empty()) {
    cur = toadd.Front();
    toadd.Pop_Front();
    bool uneventful = 1;
    Node<Seg>* p = buffer.front;
    while (p) {
      isect = Intersection(cur, p->x);
      if (isect) {
        uneventful = 0;
        diff = Difference(cur, p->x);
        buffer.Erase(p);
        if (diff.second)
          toadd.Push_Front(diff.second);
        toadd.Push_Front(isect);
        if (diff.first)
          toadd.Push_Front(diff.first);
        break;
      }
      p = p->next;
    }
    if (uneventful)
      buffer.Push_Back(cur);
  }
  Node<Seg>* p = buffer.front;
  while (p) {
    segs.push_back(p->x);
    p = p->next;
  }
  sort(segs.begin(), segs.end(), [](const Seg& p, const Seg& q) {return p.L < q.L; });
}

void Build_Edges() {
  Seg isect;
  for (int i = 0; i < n_monkeys; i++) {
    Add(s, i, monkeys[i].need);
    for (int j = 0; j < segs.size(); j++) {
      isect = Intersection(monkeys[i], segs[j]);
      if (isect)
        Add(i, n_monkeys + j, isect.Len());
    }
  }
  for (int i = 0; i < segs.size(); i++)
    Add(n_monkeys + i, t, segs[i].Len() * parallel_drinks);
}

vector<Seg> Compress(const vector<Seg>& vs) {
  vector<Seg> ans;
  for (const Seg& seg : vs) {
    if (ans.empty())
      ans.push_back(seg);
    else if (seg.L == ans.back().R)
      ans.back().R = seg.R;
    else
      ans.push_back(seg);
  }
  return ans;
}

bool Read() {
  cin >> n_monkeys;
  if (!n_monkeys || cin.eof())
    return 0;
  cin >> parallel_drinks;
  monkeys.clear();
  monkeys.resize(n_monkeys);
  for (int i = 0; i < n_monkeys; i++) {
    cin >> monkeys[i].need >> monkeys[i].L >> monkeys[i].R;
    monkeys[i].key = i;
  }

  return 1;
}

void Process() {
  cout << "Case " << ++ct << ": ";
  MONKEY_SORT_MODE = SORT_BY_R;
  sort(monkeys.begin(), monkeys.end());
  segs.clear();
  Build_Segs();
  n = n_monkeys + segs.size() + 7;
  s = n - 2;
  t = n - 3;
  adj.assign(n, vector<Edge>());
  Build_Edges();
  threads.assign(segs.size(), vector<List<Seg>>(parallel_drinks, List<Seg>()));
  for (int i = 0; i < segs.size(); i++)
    for (int j = 0; j < parallel_drinks; j++)
      threads[i][j].Push_Back(segs[i]);
  
  ll maxflow = 0, curflow, sum_of_needs = 0;
  for (int i = 0; i < n_monkeys; i++)
    sum_of_needs += monkeys[i].need;
  while (BFS()) {
    st_from.assign(n + 1, 0);
    while (1) {
      curflow = DFS(s, BIG);
      if (!curflow)
        break;
      maxflow += curflow;
    }
  }
  if (maxflow != sum_of_needs)
    cout << "No\n";
  else {
    cout << "Yes\n";
    for (int i = 0; i < n_monkeys; i++) {
      for (const Edge& edge : adj[i]) {
        if (edge.v != s && edge.v != t) {
          bool path_exists = adj[edge.v][edge.rsd].c;
          if (path_exists) {
            int j = edge.v - n_monkeys;
            List<Seg> toadd(Intersection(monkeys[i], segs[j]));
            ENTRANCE:
            while (monkeys[i].need && !toadd.Empty()) {
              Seg cur = toadd.Front();
              toadd.Pop_Front();
              for (List<Seg>& th : threads[j]) {
                Node<Seg>* p = th.front;
                while (p) {
                  Seg seg = p->x;
                  Seg isect_raw = Intersection(cur, seg);
                  if (isect_raw) {
                    Seg isect = { isect_raw.L, min(isect_raw.R, isect_raw.L + monkeys[i].need) };
                    pair<Seg, Seg> diff = Difference(cur, isect);
                    if (diff.first)
                      toadd.Push_Front(diff.first);
                    if (diff.second)
                      toadd.Push_Front(diff.second);
                    th.Erase(p);
                    diff = Difference(seg, isect);
                    if (diff.first) 
                      th.Push_Front(diff.first);
                    if (diff.second) 
                      th.Push_Front(diff.second);
                    monkeys[i].drinks.push_back(isect);
                    monkeys[i].need -= isect.Len();
                    goto ENTRANCE;
                  }
                  p = p->next;
                }
              }
            }
          }
        }
        if (!monkeys[i].need)
          break;
      }
    }
    for (int i = 0; i < n_monkeys; i++) {
      sort(monkeys[i].drinks.begin(), monkeys[i].drinks.end(),
        [](const Seg& p, const Seg& q) {return p.L < q.L; });
      monkeys[i].drinks = Compress(monkeys[i].drinks);
    }
    MONKEY_SORT_MODE = SORT_BY_KEY;
    sort(monkeys.begin(), monkeys.end());
    for (const Monkey& monkey : monkeys) {
      cout << monkey.drinks.size();
      for (const Seg& seg : monkey.drinks)
        cout << " (" << seg.L << "," << seg.R << ")";
      cout << "\n";
    }
  }
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}