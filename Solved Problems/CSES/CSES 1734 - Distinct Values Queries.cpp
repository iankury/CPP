#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

const int M = 1000000007, BIG = 0x3f3f3f3f;

int n, q;
vi x, a, b;

void Encode() {
  int encode_value = 0;
  unordered_map<int, int> encode;
  for (int i = 0; i < n; i++) {
    if (encode.count(x[i]))
      x[i] = encode[x[i]];
    else
      x[i] = encode[x[i]] = encode_value++;
  }
}

vi Sort() {
  vi ans(q);
  iota(begin(ans), end(ans), 0);
  sort(begin(ans), end(ans), [&](int p, int q) {
    const int block_start_p = a[p] / 511;
    const int block_start_q = a[q] / 511;
    if (block_start_p == block_start_q)
      return b[p] < b[q];
    return block_start_p < block_start_q;
    });
  return ans;
}

vi Process() {
  Encode();
  const vi sorted = Sort();
  vi ans(q);
  int distinct = 1, l = 0, r = 0;
  vi freq(n, 0);
  freq[0] = 1;
  for (int i : sorted) {
    const int L = a[i] - 1;
    const int R = b[i] - 1;
    while (l < L)
      if (--freq[x[l++]] == 0)
        --distinct;
    while (l > L)
      if (++freq[x[--l]] == 1)
        ++distinct;
    while (r < R)
      if (++freq[x[++r]] == 1)
        ++distinct;
    while (r > R)
      if (--freq[x[r--]] == 0)
        --distinct;
    ans[i] = distinct;
  }
  return ans;
}

void Output() {
  const vi ans = Process();
  for (int i = 0; i < q; i++)
    cout << ans[i] << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  while (cin >> n) {
    cin >> q;
    x.resize(n);
    for (int i = 0; i < n; i++)
      cin >> x[i];
    a.resize(q);
    b.resize(q);
    for (int i = 0; i < q; i++)
      cin >> a[i] >> b[i];

    Output();
  }

  return 0;
}