#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 1000000007, BIG = 0x3f3f3f3f;

string s;

double Rec(const string& p) {
  if (p[0] != '(')
    return stod(p);
  int Stack = 0;
  string temp;
  int i;
  for (i = 1; i < p.length(); i++) {
    if (p[i] == ' ') {
      i++;
      break;
    }
    temp.push_back(p[i]);
  }
  double prob = stod(temp);
  double a[2];
  for (int j = 0; j < 2; j++) {
    temp.clear();
    if (p[i] == '(') {
      int l = i;
      for (; i < p.length(); i++) {
        if (p[i] == '(')
          Stack++;
        else if (p[i] == ')') {
          Stack--;
          if (Stack == 0) {
            a[j] = Rec(p.substr(l, i + 1 - l));
            i += 2;
            break;
          }
        }
      }
    }
    else {
      for (; i < p.length(); i++) {
        if (p[i] == ' ') {
          i++;
          break;
        }
        temp.push_back(p[i]);
      }
      a[j] = stod(temp);
    }
  }
  return prob * (a[0] + a[1]) + (1. - prob) * (a[0] - a[1]);
}

int main() {
  FASTIO();

  while (getline(cin, s)) {
    if (s == "()")
      break;
    cout << fixed << setprecision(2) << Rec(s) << "\n";
  }

  return 0;
}