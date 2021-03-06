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

const int N = 500005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, a[N], pi[N], idc[N];

void Print(int idx) {
  if (pi[idx] != -1) Print(pi[idx]);
  cout << a[idx] << "\n";
}

int main() {
  FASTIO();

  n = 0;
  while (1) {
    cin >> a[n++];
    if (cin.eof()) break;
  }
  for (int i = 0; i < n; i++) pi[i] = -1;
  idc[0] = 0;
  int idc_back = 0;
  for (int i = 1; i < n; i++) {
    if (a[i] > a[idc[idc_back]]) {
      pi[i] = idc[idc_back];
      idc[++idc_back] = i;
    }
    else {
      int lb = 0, st = 0, en = idc_back;
      while (1) {
        int mid = st + (en - st) / 2;
        if (a[idc[mid]] >= a[i]) {
          if (!mid || a[idc[mid - 1]] < a[i]) {
            lb = mid;
            break;
          }
          en = mid - 1;
        }
        else st = mid + 1;
      }
      idc[lb] = i;
      pi[i] = lb ? idc[lb - 1] : -1;
    }
  }
  cout << idc_back + 1 << "\n-\n";
  Print(idc[idc_back]);

  return 0;
}