#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int n;
string s;

void Process() {
  n = s.length();
  int freq[26] = { 0 };
  for (int i = 0; i < n; i++)
    freq[s[i] - 'a']++;
  int i = 0;
  for (; i < 26; i++)
    if (freq[i] & 1)
      break;
  int j = 25;
  for (; j >= 0; j--)
    if (freq[j] & 1)
      break;
  while (i < j) {
    freq[i]++;
    freq[j]--;
    i++;
    j--;
    while (i < 26 && (freq[i] & 1) == 0)
      i++;
    while (j >= 0 && (freq[j] & 1) == 0)
      j--;
  }
  char mid = '\0';
  if (i == j)
    if (freq[i] & 1) {
      freq[i]--;
      mid = i + 'a';
    }
  for (i = 0; i < 26; i++)
    if (freq[i])
      cout << string(freq[i] / 2, i + 'a');
  if (mid)
    cout << mid;
  for (i = 25; i >= 0; i--)
    if (freq[i])
      cout << string(freq[i] / 2, i + 'a');
  cout << "\n";
}

int main() {
  FASTIO();

  while (cin >> s) {
    Process();

    if (cin.eof())
      break;
  }

  return 0;
}