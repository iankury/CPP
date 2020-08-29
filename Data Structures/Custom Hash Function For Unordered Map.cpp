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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}