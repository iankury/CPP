#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
class Treap {
	struct Node {
		int key;
		unsigned long long priority;
		Node* l, * r;
		int sz;
	};
	Node* root;
	int Size(Node* t) const { return t ? t->sz : 0; }
	void Update_Sizes(Node* t) {
		if (t)
			t->sz = 1 + Size(t->l) + Size(t->r);
	}
	void Split(Node* t, int key, Node*& l, Node*& r) {
		if (!t)
			l = r = 0;
		else if (key < t->key)
			Split(t->l, key, l, t->l), r = t;
		else
			Split(t->r, key, t->r, r), l = t;
		Update_Sizes(t);
	}
	void Merge(Node*& t, Node* l, Node* r) {
		if (!l || !r)
			t = l ? l : r;
		else if (l->priority > r->priority)
			Merge(l->r, l->r, r), t = l;
		else
			Merge(r->l, l, r->l), t = r;
		Update_Sizes(t);
	}
	void Insert(Node*& t, Node* it) {
		if (!t)
			t = it;
		else if (it->priority > t->priority)
			Split(t, it->key, it->l, it->r), t = it;
		else
			Insert(it->key < t->key ? t->l : t->r, it);
		Update_Sizes(t);
	}
	void Erase(Node*& t, int key) {
		if (t->key == key)
			Merge(t, t->l, t->r);
		else
			Erase(key < t->key ? t->l : t->r, key);
		Update_Sizes(t);
	}
	int Key_At_Pos(Node*& t, int pos, int accu) const {
		if (t->l) {
			if (t->l->sz + accu == pos - 1)
				return t->key;
			else if (t->l->sz + accu >= pos)
				return Key_At_Pos(t->l, pos, accu);
			return Key_At_Pos(t->r, pos, accu + t->l->sz + 1);
		}
		else {
			if (accu < pos - 1)
				return Key_At_Pos(t->r, pos, accu + 1);
			return t->key;
		}
	}
	void Print(Node* t) {
		if (t == 0)
			return;
		Print(t->l);
		cout << t->key << " ";
		Print(t->r);
	}
public:
	int Size() const { return Size(root); }
	bool Empty() const { return Size(root) == 0; }
	Treap() : root(0) {}
	Treap(Node* root, int sz) : root(root) {}
	void Insert(int key) { Insert(root, new Node{ key, rng(), 0, 0 }); }
	void Erase(int key) { Erase(root, key); }
	int Key_At_Pos(int pos) { return Key_At_Pos(root, pos, 0); }
	void Print() { Print(root); }
};

int main() {
	int n, x;
	cin >> n;
	Treap treap;
	vi a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		treap.Insert(i);
	}
	for (int i = 0; i < n; i++) {
		cin >> x;
		x = treap.Key_At_Pos(x);
		cout << a[x] << " ";
		treap.Erase(x);
	}

  return 0;
}