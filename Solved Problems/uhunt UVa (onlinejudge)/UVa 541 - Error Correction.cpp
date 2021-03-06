#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
bool a[N][N];

bool Read() {
  cin >> n;
  if (!n || cin.eof()) return 0;
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++) 
      cin >> a[i][j];

  return 1;
}

void Process() {
  int ans_r = -1, ans_c = -1;
  for (int i = 0; i < n; i++) {
    bool marked = 0;
    for (int j = 0; j < n; j++) 
      if (a[i][j]) marked = !marked;
    if (marked) {
      if (ans_r != -1) {
        cout << "Corrupt\n";
        return;
      }
      ans_r = i + 1;
    }
  }
  for (int j = 0; j < n; j++) {
    bool marked = 0;
    for (int i = 0; i < n; i++)
      if (a[i][j]) marked = !marked;
    if (marked) {
      if (ans_c != -1) {
        cout << "Corrupt\n";
        return;
      }
      ans_c = j + 1;
    }
  }
  if (ans_r == -1 && ans_c == -1) cout << "OK\n";
  else cout << "Change bit (" << ans_r << "," << ans_c << ")\n";
}

int main() {
  FASTIO();

  while (Read()) Process();

  return 0;
}