#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 105, M = 1000000007;

class BST {
	struct Node {
		int data;
		Node* left, *right;
	};
	Node* root = 0;
public:
	int size = 0;
	void Push(int data) {
		size++;
		Node* q = new Node;
		q->data = data;
		q->right = q->left = 0;
		if (!root) {
			root = q;
			return;
		}
		Node* p = root;
		while (1) {
			if (p->left && data < p->data)
				p = p->left;
			else if (p->right && data > p->data)
				p = p->right;
			else break;
		}
		if (data < p->data) p->left = q;
		else p->right = q;
	}
	Node* Pop(Node* node, int data) {
		if (!node) return node;
		if (data < node->data)
			node->left = Pop(node->left, data);
		else if (data > node->data)
			node->right = Pop(node->right, data);
		else
		{
			if (node->left && node->right) {
				Node* min = node->right;
				while (min->left) min = min->left;
				node->data = min->data;
				node->right = Pop(node->right, min->data);
			}
			else {
				Node* temp = node->left ? node->left : node->right;
				delete node;
				return temp;
			}
		}
		return node;
	}
	void Pop(int data) {
		size--;
		root = Pop(root, data);
	}
	int Top() {
		if (!root) return 0;
		return root->data;
	}
	void Print(Node* cur) {
		if (cur) {
			Print(cur->left);
			cout << cur->data << " ";
			Print(cur->right);
		}
	}
	void Print() {
		Print(root);
		cout << "\n";
	}
};

BST adj[N];

void Process() {
	int n, m, ans = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		adj[t1].Push(t2);
		adj[t2].Push(t1);
	}
	while (1) {
		vector<int> kick;
		for (int i = 1; i <= n; i++)
			if (adj[i].size == 1) kick.push_back(i);
		if (kick.empty()) break;
		ans++;
		for (int i = 0; i < kick.size(); i++) {
			int victim = kick[i];
			int peer = adj[victim].Top();
			if (peer) {
				adj[peer].Pop(victim);
				adj[victim].Pop(peer);
			}
		}
	}
	cout << ans << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}


/*
void DEBUG() {
	cout << "DEBUG" << ":\n";

	cout << "END OF DEBUG\n";
}
//*/