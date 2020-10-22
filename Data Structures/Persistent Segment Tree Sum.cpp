#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;

class PersistentSegTree {
	struct Node {
		ll x;
		Node* left, * right;
		Node(Node* l, Node* r, ll v) : left(l), right(r), x(v) {}
	};

	const vector<ll>& A;
	const int N;
	vector<Node*> version;

	void Build(Node* u, int p, int q) {
		if (p == q) {
			u->x = A[p];
			return;
		}
		const int mid = (p + q) / 2;
		u->left = new Node(0, 0, 0);
		u->right = new Node(0, 0, 0);
		Build(u->left, p, mid);
		Build(u->right, mid + 1, q);
		u->x = u->left->x + u->right->x;
	}

	void Update(Node* pr, Node* u, int p, int q, int i, ll val) {
		if (i > q || i < p || p > q)
			return;
		if (p == q) {
			u->x = val;
			return;
		}
		const int mid = (p + q) / 2;
		if (i <= mid) {
			u->right = pr->right;
			u->left = new Node(0, 0, 0);
			Update(pr->left, u->left, p, mid, i, val);
		}
		else {
			u->left = pr->left;
			u->right = new Node(0, 0, 0);
			Update(pr->right, u->right, mid + 1, q, i, val);
		}
		u->x = u->left->x + u->right->x;
	}

	ll RSQ(Node* u, int p, int q, int l, int r) {
		if (l > q || r < p || p > q)
			return 0;
		if (l <= p and q <= r)
			return u->x;
		const int mid = (p + q) / 2;
		return RSQ(u->left, p, mid, l, r) + RSQ(u->right, mid + 1, q, l, r);
	}
public:
	PersistentSegTree(const vector<ll>& src_arr) 
		: A(src_arr), N(int(src_arr.size())) {
		version.push_back(new Node(0, 0, 0));
		Build(version[0], 1, N - 1);
	}

	void Update(int prev_vers, int idx, ll val) {
		version.push_back(new Node(0, 0, 0));
		Update(version[prev_vers], version.back(), 1, N - 1, idx, val);
	}

	ll RSQ(int vers, int i, int j) {
		return RSQ(version[vers], 1, N - 1, i, j);
	}
};

int main() {
  io();

	

  return 0;
}