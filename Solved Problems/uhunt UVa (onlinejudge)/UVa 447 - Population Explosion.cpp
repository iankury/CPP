#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

char a[21][21];

bool In_Bounds(const int& p, const int& q) {
	return p && q && p < 21 && q < 21;
}

int Neigh(const int& p, const int& q) {
	int ans = 0;
	for (int r = p - 1; r < p + 2; r++) for (int c = q - 1; c < q + 2; c++)
		if (In_Bounds(r, c) && a[r][c] == 'O') ans++;
	return a[p][q] == 'O' ? ans - 1 : ans;
}

void Print() {
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 20; j++) cout << a[i][j];
		cout << "\n";
	}
	cout << "********************\n";
}

void Process() {
	cout << "********************\n";
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 20; j++) a[i][j] = ' ';
	int n, row, col;
	cin >> n;
	cin.ignore();
	string s;
	while (getline(cin, s), s.size() && isdigit(s[0])) {
		stringstream ss;
		ss << s;
		ss >> row >> col;
		a[row][col] = 'O';
	}
	Print();
	while (--n) {
		vector<char*> to_die, to_thrive;
		for (int i = 1; i <= 20; i++) {
			for (int j = 1; j <= 20; j++) {
				int neigh = Neigh(i, j);
				if (a[i][j] == 'O' && (neigh < 2 || neigh > 3)) to_die.push_back(&a[i][j]);
				else if (a[i][j] == ' ' && neigh == 3) to_thrive.push_back(&a[i][j]);
			}
		}
		for (auto& x : to_die) *x = ' ';
		for (auto& x : to_thrive) *x = 'O';
		Print();
	}
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) {
		Process();
		if (T) cout << "\n";
	}

	return 0;
}