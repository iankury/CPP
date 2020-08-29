#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
string s;

bool Read() {
  string r;
  s.clear();
  while (cin >> r) {
    if (r == "ENDPROGRAM")
      break;
    if (r == "IF")
      s.push_back('i');
    else if (r == "ELSE")
      s.push_back('e');
    else if (r == "END_IF")
      s.push_back('n');
  }

  return 1;
}

ll Rec(const string& p) {
  if (p.empty())
    return 1;
  int idxe, idxn;
  int Stack = 0;
  for (int i = 0; i < p.length(); i++) {
    if (p[i] == 'i')
      Stack++;
    else if (p[i] == 'n') {
      Stack--;
      if (Stack == 0) {
        idxn = i;
        break;
      }
    }
    else if (p[i] == 'e') {
      if (Stack == 1)
        idxe = i;
    }
  }
  ll r1 = 1, r2 = 1, r3 = 1;
  if (idxe > 1) 
    r1 = Rec(p.substr(1, idxe - 1));
  if (idxn - idxe > 1)
    r2 = Rec(p.substr(idxe + 1, idxn - idxe - 1));
  if (idxn < p.length() - 1)
    r3 = Rec(p.substr(idxn + 1));
  return (r1 + r2) * r3;
}

void Process() {
  cout << Rec(s) << "\n";
}

int main() {
  FASTIO();

  int T;
  cin >> T;
  while (T-- && Read())
    Process();

  return 0;
}