#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 2147483647;

class Fenwick_Tree {
	vi ft;
	int n;
public: Fenwick_Tree(int _n) : n(_n + 1) { ft.assign(_n + 1, 0); }
	void Adjust(int key, int delta) { for (; key < n; key += key & -key) ft[key] += delta; }
	void Set(int key, int x) { Adjust(key, x - ft[key]); }
	int RSQ(int x) { int ans = 0; while (x) { ans += ft[x]; x -= x & -x; } return ans; }
	int RSQ(int lo, int hi) { return RSQ(hi) - RSQ(lo - 1); }
};

void Process() {

}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}