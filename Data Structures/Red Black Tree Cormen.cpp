#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

template <class T>
class RedBlackTree {
	struct Node { T key; bool red; Node* L, *R, *P; };
	Node* root, *nil;
	void Left_Rotate(Node* x) {
		Node* y = x->R;
		x->R = y->L;
		if (y->L != nil) y->L->P = x;
		y->P = x->P;
		if (x->P == nil) root = y;
		else if (x == x->P->L) x->P->L = y;
		else x->P->R = y;
		y->L = x;
		x->P = y; 
	}
	void Right_Rotate(Node* x) {
		Node* y = x->L;
		x->L = y->R;
		if (y->R != nil) y->R->P = x;
		y->P = x->P;
		if (x->P == nil) root = y;
		else if (x == x->P->L) x->P->L = y;
		else x->P->R = y;
		y->R = x;
		x->P = y;
	}
	void Transplant(Node* u, Node* v) {
		if (u->P == nil) root = v;
		else if (u == u->P->L) u->P->L = v;
		else u->P->R = v;
		v->P = u->P;
	}
	Node* Minimum_Node(Node* u) {
		Node* ans = nil;
		while (u != nil) {
			ans = u;
			u = u->L;
		}
		return ans;
	}
	Node* Maximum_Node(Node* u) {
		Node* ans = nil;
		while (u != nil) {
			ans = u;
			u = u->R;
		}
		return ans;
	}
	void Print(Node* u) {
		if (u != nil) {
			Print(u->L);
			cout << u->key << " "; 
			Print(u->R);
		}
	}
	Node* Find(T key) {
		Node* x = root;
		while (x != nil) {
			if (x->key == key) return x;
			if (x->key > key) x = x->L;
			else x = x->R;
		}
		return nil;
	}
public:
	RedBlackTree() : nil(new Node{ 0, 0, 0, 0, 0 }) { root = nil; }
	void Insert(T key) {
		Node* z = new Node{ key, 1, nil, nil, nil }, *y = nil, *x = root;
		while (x != nil) {
			y = x;
			x = z->key < x->key ? x->L : x->R;
		}
		z->P = y;
		if (y == nil) root = z;
		else if (z->key < y->key) y->L = z;
		else y->R = z;
		while (z->P->red) { // fixup
			if (z->P == z->P->P->L) {
				y = z->P->P->R;
				if (y->red) {
					z->P->red = 0;
					y->red = 0;
					z->P->P->red = 1;
					z = z->P->P;
				}
				else {
					if (z == z->P->R) {
						z = z->P;
						Left_Rotate(z);
					}
					z->P->red = 0;
					z->P->P->red = 1;
					Right_Rotate(z->P->P);
				}
			}
			else {
				y = z->P->P->L;
				if (y->red) {
					z->P->red = 0;
					y->red = 0;
					z->P->P->red = 1;
					z = z->P->P;
				}
				else {
					if (z == z->P->L) {
						z = z->P;
						Right_Rotate(z);
					}
					z->P->red = 0;
					z->P->P->red = 1;
					Left_Rotate(z->P->P);
				}
			}
		}
		root->red = 0;
	}
	bool Contains(T key) { return Find(key) != nil; }
	T Min_Key() {
		T ans = T();
		Node* u = Minimum_Node(root);
		return u == nil ? ans : u->key;
	}
	T Max_Key() {
		T ans = T();
		Node* u = Maximum_Node(root);
		return u == nil ? ans : u->key;
	}
	void Delete(T key) {
		Node* z = Find(key);
		if (z == nil) return;
		Node* y = z, *x = nil;
		bool y_backup_color = y->red;
		if (z->L == nil) {
			x = z->R;
			Transplant(z, z->R);
		}
		else if (z->R == nil) {
			x = z->L;
			Transplant(z, z->L);
		}
		else {
			y = Minimum_Node(z->R);
			y_backup_color = y->red;
			x = y->R;
			if (y->P == z) x->P = y;
			else {
				Transplant(y, y->R);
				y->R = z->R;
				y->R->P = y;
			}
			Transplant(z, y);
			y->L = z->L;
			y->L->P = y;
			y->red = z->red;
		}
		if (!y_backup_color) {
			while (x != root && !x->red) {
				Node* w = nil;
				if (x == x->P->L) { // one
					w = x->P->R;
					if (w->red) {
						w->red = 0;
						x->P->red = 1;
						Left_Rotate(x->P);
						w = x->P->R;
					}
					if (!(w->L->red || w->R->red)) {
						w->red = 1;
						x = x->P;
					}
					else {
						if (!w->R->red) {
							w->L->red = 0;
							w->red = 1;
							Right_Rotate(w);
							w = x->P->R;
						}
						w->red = x->P->red;
						x->P->red = w->R->red = 0;
						Left_Rotate(x->P);
						x = root;
					}
				}
				else { // two
					w = x->P->L;
					if (w->red) {
						w->red = 0;
						x->P->red = 1;
						Right_Rotate(x->P);
						w = x->P->L;
					}
					if (!(w->L->red || w->R->red)) {
						w->red = 1;
						x = x->P;
					}
					else {
						if (!w->L->red) {
							w->R->red = 0;
							w->red = 1;
							Left_Rotate(w);
							w = x->P->L;
						}
						w->red = x->P->red;
						x->P->red = w->L->red = 0;
						Right_Rotate(x->P);
						x = root;
					}
				}
			}
			x->red = 0;
		}
	}
	void Print() { 
		if (root == nil) cout << "The tree is empty.\n"; 
		else {
			Print(root); 
			cout << "\n";
		}
	}
};

void Process() {
	string s;
	int y;
	RedBlackTree<int> t;
	while (1) {
		cin >> s;
		if (s == "ins") {
			cin >> y;
			if(!t.Contains(y)) t.Insert(y);
		}
		else if (s == "del") {
			cin >> y;
			t.Delete(y);
		}
		else if (s == "find") {
			cin >> y;
			if (t.Contains(y)) cout << "The tree contains an element " << y << ".\n";
			else cout << y << " is not an element of the tree.\n";
		}
		else if (s == "min") cout << "Tree minimum value: " << t.Min_Key() << ".\n";
		else if (s == "max") cout << "Tree maximum value: " << t.Max_Key() << ".\n";
		else if (s == "print") t.Print();
		else break;
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}