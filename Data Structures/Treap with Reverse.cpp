#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
class Treap {
	struct Node {
		int key;
		unsigned long long priority;
		int sz;
		bool reversed;
		Node* l;
		Node* r;
		Node(int key) : key(key), priority(rng()), sz(1), reversed(0), l(0), r(0) {}
	};
	Node* root;
	int Size(Node* t) {
		return t ? t->sz : 0;
	}
	void Update(Node* t) {
		if (!t)
			return;
		t->sz = Size(t->l) + 1 + Size(t->r);
	}
	void Push(Node* t) {
		if (t && t->reversed) {
			t->reversed = 0;
			swap(t->l, t->r);
			if (t->l) t->l->reversed ^= 1;
			if (t->r) t->r->reversed ^= 1;
		}
	}
	void Merge(Node*& t, Node* l, Node* r) {
		Push(l);
		Push(r);
		if (!l || !r)
			t = l ? l : r;
		else if (l->priority > r->priority) {
			t = l;
			Merge(l->r, l->r, r);
		}
		else {
			t = r;
			Merge(r->l, l, r->l);
		}
		Update(t);
	}
	pair<Node*, Node*> Split(Node* t, int key, int add = 0) {
		if (!t)
			return { 0, 0 };
		Push(t);
		int cur_key = add + Size(t->l);
		pair<Node*, Node*> ans;
		if (key <= cur_key) {
			auto [nl, nr] = Split(t->l, key, add);
			t->l = nr;
			ans.first = nl;
			ans.second = t;
		}
		else {
			auto [nl, nr] = Split(t->r, key, cur_key + 1);
			t->r = nl;
			ans.first = t;
			ans.second = nr;
		}
		Update(t);
		return ans;
	}
public:
	Treap() : root(0) {}
	void Insert(Node*& t, int key, int pos) {
		Push(t);
		auto [t1, t2] = Split(t, pos);
		t = new Node(key);
		Merge(t, t1, t);
		Merge(t, t, t2);
	}
	void Insert(int key, int pos) {
		if (root)
			Insert(root, key, pos);
		else
			root = new Node(key);
	}
	void Insert(int key) {
		if (root)
			Insert(root, key, Size(root));
		else
			root = new Node(key);
	}
	int Erase(Node*& t, int pos) {
		Push(t);
		Node* t1, * t2, * t3;
		tie(t1, t2) = Split(t, pos);
		tie(t2, t3) = Split(t2, 1);
		Merge(t, t1, t3);
		int ans = t2->key;
		delete t2;
		return ans;
	}
	int Erase(int pos) { return Erase(root, pos); }
	void Reverse(Node* t, int l, int r) {
		Node* t1, * t2, * t3;
		tie(t1, t2) = Split(t, l);
		tie(t2, t3) = Split(t2, r - l + 1);
		t2->reversed ^= 1;
		Merge(t, t1, t2);
		Merge(t, t, t3);
	}
	void Reverse(int l, int r) { Reverse(root, l, r); }
	int Key_At_Pos(Node* t, int pos, int add = 0) {
		if (!t)
			return -1;
		Push(t);
		int cur_key = add + Size(t->l);
		if (pos < cur_key)
			return Key_At_Pos(t->l, pos, add);
		else if (pos == cur_key)
			return t->key;
		return Key_At_Pos(t->r, pos, cur_key + 1);
	}
	int Key_At_Pos(int pos) { return Key_At_Pos(root, pos); }
	vi To_Vector() {
		vi ans(Size(root));
		for (int i = 0; i < Size(root); i++)
			ans[i] = Key_At_Pos(root, i);
		return ans;
	}
};

int main() {
	

  return 0;
}