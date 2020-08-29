#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n, ans[N];

enum { GUEST_ARRIVED, ROOM_FREED };

struct Event {
  bool type;
  int t, x, idx;
  bool operator < (const Event& ev) const {
    return t == ev.t ? type && !ev.type : t > ev.t;
  }
};

priority_queue<Event> events;

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  int u, v;
  for (int i = 1; i <= n; i++) {
    cin >> u >> v;
    events.push({ GUEST_ARRIVED, u, v, i });
  }

  return 1;
}

void Process() {
  int mx = 0;
  stack<int> rooms;
  for (int i = n; i; i--)
    rooms.push(i);
  Event cur;
  while (!events.empty()) {
    cur = events.top();
    events.pop();
    if (cur.type == GUEST_ARRIVED) {
      mx = max(mx, rooms.top());
      ans[cur.idx] = rooms.top();
      events.push({ ROOM_FREED, cur.x, rooms.top() });
      rooms.pop();
    }
    else 
      rooms.push(cur.x);
  }
  cout << mx << "\n";
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