#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

constexpr ll NIL = ll(-1e18);
class SegTree {
	struct Node {
		int len, L, R;
		ll sum, set = NIL, add = 0;
		operator ll () const { return sum; }
		Node& operator = (ll val) { sum = val; return *this; }
		Node& operator += (ll val) { sum += val; return *this; }
		void Clear() { set = NIL, add = 0; }
	};
	vector<Node> t;
	const vi& src_arr;
	int i, j, x;
	bool overwrite;
	void Build(int p, int _L, int _R) {
		Node& u = t[p];
		u.L = _L, u.R = _R;
		u.len = _R + 1 - _L;
		if (_L == _R) {
			u = src_arr[_L];
			return;
		}
		const int l = (p << 1), r = l + 1, mid = (_L + _R) / 2;
		Build(l, _L, mid), Build(r, mid + 1, _R);
		u = t[l] + t[r];
	}
	ll RSQ(int p) {
		Node& u = t[p];
		if (j < u.L || i > u.R)
			return 0;
		Run_Pending(p);
		if (u.L >= i && u.R <= j)
			return u;
		return RSQ(p << 1) + RSQ((p << 1) + 1);
	}
	void Propagate(int p) {
		Node& u = t[p];
		const Node& pi = t[p >> 1];
		if (pi.set == NIL) {
			u.add += pi.add;
			return;
		}
		u.set = pi.set, u.add = pi.add;
	}
	void Run_Pending(int p) {
		Node& u = t[p];
		if (u.set != NIL)
			u = u.set * u.len;
		u += u.add * u.len;
		if (u.len > 1) {
			Propagate(p << 1);
			Propagate((p << 1) + 1);
		}
		u.Clear();
	}
	void Edit_Range(int p) {
		Node& u = t[p];
		if (j < u.L || i > u.R)
			return;
		if (u.L >= i && u.R <= j) {
			if (overwrite)
				u.set = x, u.add = 0;
			else
				u.add += x;
			return;
		}
		const int l = (p << 1), r = l + 1;
		Run_Pending(p), Edit_Range(l), Edit_Range(r), Run_Pending(l), Run_Pending(r);
		u = t[l] + t[r];
	}
public:
	SegTree(const vi& _a) : src_arr(_a) {
		t.resize(_a.size() << 2);
		Build(1, 1, int(_a.size()) - 1);
	}
	ll RSQ(int i, int j) {
		this->i = i, this->j = j;
		return RSQ(1);
	}
	void Edit_Range(int i, int j, int x, bool overwrite) {
		this->i = i, this->j = j, this->x = x, this->overwrite = overwrite;
		Edit_Range(1);
	}
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  

  return 0;
}