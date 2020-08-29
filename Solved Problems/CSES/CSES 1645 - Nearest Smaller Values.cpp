#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

struct Node {
	int idx, key;
	bool operator < (Node& node) const {
		return idx < node.idx;
	}
};

int ct = 0;
int n;

vector<Node> a;
vi ans;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  a.resize(n + 1);
  ans.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i].key;
    a[i].idx = i;
  }

  return 1;
}

void Process() {
  sort(begin(a) + 1, end(a), [](const Node& p, const Node& q) {
    return p.key < q.key;
    }); 
  set<int> S;
  set<int>::iterator it;
  vi pending;
  int lb = 0;
	for (int i = 1; i <= n; i++) {
    if (a[i].key > lb) {
      lb = a[i].key;
      S.insert(begin(pending), end(pending));
      pending.clear();
    }
    pending.push_back(a[i].idx);
    it = S.upper_bound(a[i].idx);
    if (it == S.begin())
      ans[a[i].idx] = 0;
    else
      ans[a[i].idx] = *prev(it);
	}
  for (int i = 1; i <= n; i++)
    cout << ans[i] << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  while (Read())
    Process();

  return 0;
}