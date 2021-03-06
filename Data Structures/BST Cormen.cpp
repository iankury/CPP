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

class BST {
	struct Node { int key; Node* P, *L, *R; };
	Node* root;
	Node* Minimum(Node* _root) {
		if (!_root) return 0;
		Node* walker = _root;
		while (walker->L) walker = walker->L;
		return walker;
	}
	Node* Maximum(Node* _root) {
		if (!_root) return 0;
		Node* walker = _root;
		while (walker->R) walker = walker->R;
		return walker;
	}
	Node* Find(int key) {
		Node* walker = root;
		while (walker) {
			if (key == walker->key) return walker;
			if (key < walker->key) walker = walker->L;
			else walker = walker->R;
		}
		return 0;
	}
	void Transplant(Node* weed, Node* sprout) {
		if (!weed->P) root = sprout;
		else {
			if (weed->P->L && weed->P->L == weed) weed->P->L = sprout;
			else weed->P->R = sprout;
		}
		if (sprout) sprout->P = weed->P;
	}
public:
	BST() : root(0) {}
	void Push(int key) {
		Node* push_me = new Node{ key, 0, 0, 0 };
		if (root) {
			Node* walker = root, *parent = 0;
			while (walker) {
				parent = walker;
				if (push_me->key < walker->key) walker = walker->L;
				else walker = walker->R;
			}
			if (push_me->key < parent->key) parent->L = push_me;
			else parent->R = push_me;
			push_me->P = parent;
		}
		else root = push_me;
	}
	int Minimum() {
		Node* min = Minimum(root);
		return min ? min->key : -1;
	}
	int Maximum() {
		Node* max = Maximum(root);
		return max ? max->key : -1;
	}
	bool Contains(int key) { return Find(key); }
	int Predecessor(int key) {
		Node* p = Find(key);
		if (!p) return -1;
		if (p->L) return Maximum(p->L)->key;
		while (p) {
			if (p->key < key) return p->key;
			p = p->P;
		}
		return -1;
	}
	int Successor(int key) {
		Node* p = Find(key);
		if (!p) return -1;
		if (p->R) return Minimum(p->R)->key;
		while (p) {
			if (p->key > key) return p->key;
			p = p->P;
		}
		return -1;
	}
	void Delete(int key) {
		Node* victim = Find(key);
		if (!victim) return;
		if (!victim->L) Transplant(victim, victim->R);
		else if (!victim->R) Transplant(victim, victim->L);
		else {
			Node* suc = Minimum(victim->R);
			if (suc != victim->R) {
				Transplant(suc, suc->R);
				suc->R = victim->R;
				suc->R->P = suc;
			}
			Transplant(victim, suc);
			suc->L = victim->L;
			suc->L->P = suc;
		}
		delete victim;
	}
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