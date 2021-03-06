#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;

const int N = 100005, M = 1000000007;

struct Node { string s; int sz; };

string Root(map<string, Node>& root, const string& p) {
	return root[p].s == p ? p : root[p].s = Root(root, root[p].s);
}

void U(map<string, Node>& root, const string& p, const string& q) {
	string r = Root(root, p), t = Root(root, q);
	if (r == t) return;
	root[t].sz = root[r].sz + root[t].sz;
	root[r].s = root[t].s;
}

void Process() {
	map<string, Node> root;
	int n;
	cin >> n;
	string p, q;
	for (int i = 0; i < n; i++) {
		cin >> p >> q;
		if (!root.count(p)) root[p] = { p, 1 };
		if (!root.count(q)) root[q] = { q, 1 };
		if (p != q) U(root, p, q);
		cout << root[Root(root, p)].sz << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}