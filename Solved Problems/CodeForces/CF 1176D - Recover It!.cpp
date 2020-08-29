#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 200005, M = 3000123, BIG = 0x3f3f3f3f;

int ct = 0;
int n;
int freq[M];
bool prime[M];
vi primeList;

void Sieve() {
  memset(prime, 1, sizeof prime);
  prime[0] = prime[1] = 0;
  for (int i = 2; i * i < M; i++)
    if (prime[i])
      for (int j = i * i; j < M; j += i)
        prime[j] = 0;
  primeList.reserve(N);
  for (int i = 2; i < M; i++)
    if (prime[i])
      primeList.push_back(i);
}

bool Read() {
  cin >> n;
  if (cin.eof())
    return 0;
  memset(freq, 0, sizeof freq);
  int u;
  for (int i = 0; i < 2 * n; i++) {
    cin >> u;
    freq[u]++;
  }

  return 1;
}

void Process() {
  vi ans;
  ans.reserve(n);
  int div;
  for (int i = N; i > 1; i--) 
    if (!prime[i]) {
      for (div = 2; div * div <= i; div++)
        if (i % div == 0) {
          div = i / div;
          break;
        }
      while (freq[div] && freq[i]) {
        ans.push_back(i);
        freq[div]--;
        freq[i]--;
      }
    }
  for (int i = 2; i < N; i++)
    if (prime[i]) {
      while (freq[primeList[i - 1]] && freq[i]) {
        ans.push_back(i);
        freq[primeList[i - 1]]--;
        freq[i]--;
      }
    }
  for (int x : ans)
    cout << x << " ";
  cout << "\n";
}

int main() {
  FASTIO();

  Sieve();

  while (Read())
    Process();

  return 0;
}