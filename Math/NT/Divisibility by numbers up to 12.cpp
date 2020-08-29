#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;
int n;
bool vis[20];

bool Read() {
  cin >> s >> n;
  memset(vis, 0, sizeof vis);
  int temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    vis[temp] = 1;
  }

  return 1;
}

struct Roll {
  int r[6] = { 1,3,2,-1,-3,-2 };
  int idx;
  Roll(): idx(5){}
  int Next() {
    if (++idx > 5)
      idx = 0;
    return r[idx];
  }
};

bool Solve() {
  bool no[20] = { 0 };
  int lastDigit = s.back() - '0';
  ll sum = 0, sum2 = 0;
  Roll roll;
  string lastTwo = s.substr(max(0, (int)s.length() - 2));
  string lastThree = s.substr(max(0, (int)s.length() - 3));
  for (int i = 0; i < s.length(); i++)
    sum += s[i] - '0';
  no[2] = lastDigit % 2;
  no[3] = sum % 3;
  no[4] = stoi(lastTwo) % 4;
  no[5] = !(lastDigit == 0 || lastDigit == 5);
  no[6] = no[2] || no[3];
  for (int i = s.length() - 1; i >= 0; i--) 
    sum2 += (s[i] - '0') * roll.Next();
  no[7] = sum2 % 7;
  no[8] = stoi(lastThree) % 8;
  no[9] = sum % 9;
  no[10] = lastDigit != 0;
  sum2 = 0;
  for (int i = 0; i < s.length(); i++) {
    if (i & 1)
      sum2 -= s[i] - '0';
    else
      sum2 += s[i] - '0';
  }
  no[11] = sum2 % 11;
  no[12] = no[3] || no[4];
  for (int i = 2; i < 13; i++)
    if (vis[i] && no[i]) 
      return 0;
  return 1;
}

void Process() {
  cout << s << " - ";
  if (Solve())
    cout << "Wonderful.\n";
  else
    cout << "Simple.\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}