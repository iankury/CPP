#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int Succ(int u) { return u + 1; }
void Floyd_Cycle(int x0, int& mu, int& lambda) {
  int tortoise = Succ(x0), hare = Succ(Succ(x0));
  while (tortoise != hare) {
    tortoise = Succ(tortoise);
    hare = Succ(Succ(hare));
  }
  mu = 0;
  hare = x0;
  while (tortoise != hare) {
    tortoise = Succ(tortoise);
    hare = Succ(hare); mu++;
  }
  lambda = 1;
  hare = Succ(tortoise);
  while (tortoise != hare) {
    hare = Succ(hare);
    lambda++;
  }
}

int main() {
  FASTIO();

  return 0;
}