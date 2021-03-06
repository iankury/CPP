#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;

const int N = 100005, M = 1000000007;

void Process() {
	while (!cin.eof()) {
		int r, c, k, x;
		if (!(cin >> r >> c)) break;
		if (c == -1) break;
		vector<vector<ii>> a;
		a.resize(c);
		for (int i = 1; i <= r; i++) {
			cin >> k;
			vector<int> b;
			for (int j = 0; j < k; j++) {
				cin >> x;
				b.push_back(x);
			}
			for (int j = 0; j < k; j++) {
				cin >> x;
				a[b[j] - 1].push_back({ i, x });
			}
		}
		cout << c << " " << r << "\n";
		for (auto& row : a) {
			if (row.empty()) cout << "0\n\n";
			else {
				cout << row.size();
				for (int j = 0; j < row.size(); j++)
					cout << " " << row[j].first;
				cout << "\n";
				for (int j = 0; j < row.size(); j++)
					cout << (j ? " " : "") << row[j].second;
				cout << "\n";
			}
		}
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}