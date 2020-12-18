#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
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

class DistinctValuesInRange {
  const int n, q;
  vi& values;
  vi& queries_from;
  vi& queries_to;
  vi sorted;
  void Encode() {
    int encode_value = -1;
    unordered_map<int, int, custom_hash> encode;
    for (int i = 0; i < n; i++) {
      if (!encode.count(values[i]))
        encode[values[i]] = ++encode_value;
      values[i] = encode[values[i]];
    }
  }
  void Sort() {
    const int SQRT = 511;
    iota(begin(sorted), end(sorted), 0);
    sort(begin(sorted), end(sorted), [&](int p, int q) {
      const int block_start_p = queries_from[p] / SQRT;
      const int block_start_q = queries_from[q] / SQRT;
      if (block_start_p == block_start_q)
        return queries_to[p] < queries_to[q];
      return block_start_p < block_start_q;
      });
  }
  void Process() {
    ans.resize(q);
    int distinct = 1, l = 0, r = 0;
    vi freq(n);
    freq[0] = 1;
    for (int i : sorted) {
      const int L = queries_from[i] - 1;
      const int R = queries_to[i] - 1;
      while (l < L)
        if (--freq[values[l++]] == 0)
          --distinct;
      while (l > L)
        if (++freq[values[--l]] == 1)
          ++distinct;
      while (r < R)
        if (++freq[values[++r]] == 1)
          ++distinct;
      while (r > R)
        if (--freq[values[r--]] == 0)
          --distinct;
      ans[i] = distinct;
    }
  }
public:
  vi ans;
  DistinctValuesInRange(
    vi& values,
    vi& queries_from,
    vi& queries_to
  ) :
    values(values),
    queries_from(queries_from),
    queries_to(queries_to),
    n(values.size()),
    q(queries_from.size()) {
    sorted.resize(q);
    Encode();
    Sort();
    Process();
  }
}; // Mutates input! Indexing from 0. Attention: L/R offset!

int main() {
  io();

  

  return 0;
}