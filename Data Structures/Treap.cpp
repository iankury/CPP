#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
class Treap {
	struct Node {
		int key;
		unsigned long long priority;
		Node* l, * r;
		int sz, freq;
	};
	Node* root;
	int Size(Node* t) const { return t ? t->sz + t->freq - 1 : 0; }
	void Update_Sizes(Node* t) {
		if (t)
			t->sz = 1 + Size(t->l) + Size(t->r);
	}
	void Update_Recursive(Node* t, int key) {
		if (t->key < key)
			Update_Recursive(t->r, key);
		else if (t->key > key)
			Update_Recursive(t->l, key);
		Update_Sizes(t);
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
	Node* Find(Node* t, int key) const {
		if (t->key == key)
			return t;
		if (t->key < key)
			return t->r ? Find(t->r, key) : 0;
		return t->l ? Find(t->l, key) : 0;
	}
	int Key_At_Pos(Node* t, int pos, int accu) const {
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
		cout << t->key << "(" << t->freq << ") sz " << Size(t) << " LR: " <<
			(t->l ? t->l->key : -1) << ", " << (t->r ? t->r->key : -1) << "\n";
		Print(t->l);
		Print(t->r);
	}
	int Lower_Bound(Node* t, int key, int accu) const {
		if (t->key < key) {
			if (t->r)
				return Lower_Bound(t->r, key, accu + t->freq + Size(t->l));
			return accu + Size(t);
		}
		else if (t->key > key) {
			if (t->l)
				return Lower_Bound(t->l, key, accu);
			return accu;
		}
		else {
			if (t->l) {
				if (t->l->key == key)
					return Lower_Bound(t->l, key, accu);
				return accu + Size(t->l);
			}
			return accu;
		}
	}
	int Upper_Bound(Node* t, int key, int accu) const {
		if (t->key <= key) {
			if (t->r)
				return Upper_Bound(t->r, key, accu + t->freq + Size(t->l));
			return accu + Size(t);
		}
		else {
			if (t->l)
				return Upper_Bound(t->l, key, accu);
			return accu;
		}
	}
public:
	int Size() const { return Size(root); }
	bool Empty() const { return Size(root) == 0; }
	Treap() : root(0) {}
	Treap(Node* root, int sz) : root(root) {}
	Node* Find(int key) { return Find(root, key); }
	void Insert(int key) {
		if (root) {
			Node* p = Find(key);
			if (p) {
				p->freq++;
				Update_Recursive(root, key);
				return;
			}
		}
		Node* p = new Node{ key, rng(), 0, 0, 0, 1 };
		Insert(root, p);
		if (p->priority > root->priority)
			root = p;
	}
	void Erase(int key) {
		Node* p = Find(key);
		if (p) {
			if (p->freq > 1) {
				p->freq--;
				Update_Recursive(root, key);
			}
			else 
				Erase(root, key);
		}
	}
	int Key_At_Pos(int pos) { return Key_At_Pos(root, pos, 0); }
	void Print() { Print(root); cout << "\n"; }
	int Lower_Bound(int key) { return Lower_Bound(root, key, 0); }
	int Upper_Bound(int key) { return Upper_Bound(root, key, 0); }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	return 0;
}