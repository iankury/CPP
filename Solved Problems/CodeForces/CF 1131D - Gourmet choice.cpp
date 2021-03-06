#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 2006, M = 1000000007, BIG = 0x3f3f3f3f;
int n, m;
vector<vi> adj(N);
vi a(N), d(N), root(N), ans;
queue<int> Q;
bitset<N> vis;
char matrix[1001][1001];

int Root(int p) { return p == root[p] ? p : root[p] = Root(root[p]); }
void Union(int p, int q) { root[Root(p)] = Root(q); }

bool Sort() {
	int cur = 1, idx = 1;
	for (int i = 1; i <= n; i++) if (!d[Root(i)]) Q.push(i);
	for (int i = 1002; i <= m + 1001; i++) if (!d[Root(i)]) Q.push(i);
	while (!Q.empty()) {
		cur = Q.front();
		Q.pop();
		if (vis[cur]) return 0;
		vis[cur] = 1;
		a[idx++] = cur;
		for (auto x : adj[Root(cur)]) if (--d[Root(x)] == 0) Q.push(x);
	}
	return 1;
}

void Process() {
	vis.reset();
	cin >> n >> m;
	d.assign(N, 0);
	for (int i = 0; i < N; i++) root[i] = i;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> matrix[i][j];
			if (matrix[i][j] == '=') Union(i, j + 1001);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (matrix[i][j] == '=') {
				if (Root(i) != Root(j + 1001)) {
					cout << "No\n";
					return;
				}
			}
			else {
				if (Root(i) == Root(j + 1001)) {
					cout << "No\n";
					return;
				}
				if (matrix[i][j] == '<') {
					adj[Root(j + 1001)].push_back(i);
					d[Root(i)]++;
				}
				else if (matrix[i][j] == '>') {
					adj[Root(i)].push_back(j + 1001);
					d[Root(j + 1001)]++;
				}
			}
		}
	}
	if (!Sort()) {
		cout << "No\n";
		return;
	}
	ans.assign(N, 0);
	int eval = 1;
	for (int i = n + m; i; i--) {
		if (!ans[Root(a[i])]) {
			for (auto& x : adj[Root(a[i])]) {
				if (ans[Root(x)] >= eval) {
					eval = ans[Root(x)] + 1;
				}
			}
			ans[Root(a[i])] = eval;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!ans[Root(i)]) {
			cout << "No\n";
			return;
		}
	}
	for (int i = 1002; i <= m + 1001; i++) {
		if (!ans[Root(i)]) {
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) cout << ans[Root(i)] << " ";
	cout << "\n";
	for (int i = 1002; i <= m + 1001; i++) cout << ans[Root(i)] << " ";
	cout << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}