#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctype.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int n, m, cur_idx;
char type, cur;
string s, ans;

bool Read() {
	cin >> type;
	if (cin.eof() || type == '#') return 0;
	cin >> n >> m;
	s.clear();
	char c;
	if (type == 'B') {
		while (cin >> c) {
			if (isdigit(c)) s.push_back(c);
			else {
				cin.putback(c);
				break;
			}
		}
	}
	else cin >> s;

	return 1;
}

int Coor_to_idx(int i, int j) { return i * m + j; }

void TOD(int i1, int i2, int j1, int j2) {
	if (i1 > i2 || j1 > j2) return;
	bool all_same = 1;
	char fst = s[Coor_to_idx(i1, j1)];
	for (int i = i1; i <= i2 && all_same; i++) 
		for (int j = j1; j <= j2 && all_same; j++) 
			if (s[Coor_to_idx(i, j)] != fst) all_same = 0;
	if (all_same) ans.push_back(fst);
	else {
		ans.push_back('D');
		int mid_i = i1 + (i2 - i1) / 2, mid_j = j1 + (j2 - j1) / 2;
		TOD(i1, mid_i, j1, mid_j);
		TOD(i1, mid_i, mid_j + 1, j2);
		TOD(mid_i + 1, i2, j1, mid_j);
		TOD(mid_i + 1, i2, mid_j + 1, j2);
	}
}

void Fill(char c, int i1, int i2, int j1, int j2) {
	for (int i = i1; i <= i2; i++)
		for (int j = j1; j <= j2; j++)
			ans[Coor_to_idx(i, j)] = c;
}

void TOB(int i1, int i2, int j1, int j2) {
	if (i1 > i2 || j1 > j2) return;
	if (cur_idx >= s.length()) return;
	cur = s[cur_idx++];
	if (cur == 'D') {
		int mid_i = i1 + (i2 - i1) / 2, mid_j = j1 + (j2 - j1) / 2;
		TOB(i1, mid_i, j1, mid_j);
		TOB(i1, mid_i, mid_j + 1, j2);
		TOB(mid_i + 1, i2, j1, mid_j);
		TOB(mid_i + 1, i2, mid_j + 1, j2);
	}
	else Fill(cur, i1, i2, j1, j2);
}

void Print() {
	for (int i = 0; i < ans.length(); i++) {
		cout << ans[i];
		if (!((i + 1) % 50)) cout << "\n";
	}
	if (ans.length() % 50) cout << "\n";
}

void Process() {
	if (type == 'B') {
		ans.clear();
		cout << "D" << right << setw(4) << n << right << setw(4) << m << "\n";
		TOD(0, n - 1, 0, m - 1);
	}
	else {
		ans.resize(n * m);
		cout << "B" << right << setw(4) << n << right << setw(4) << m << "\n";
		cur_idx = 0;
		TOB(0, n - 1, 0, m - 1);
	}
	Print();
}

int main() {
	FASTIO();

	while (Read()) Process();

	return 0;
}