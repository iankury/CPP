#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;
map<int, int> DAYS{
	{1,31},{2,28},{3,31},{4,30},{5,31},{6,30},
	{7,31},{8,31},{9,30},{10,31},{11,30},{12,31}
};
struct Date { 
	int d, m, y; 
	bool operator == (const Date& x) const { return d == x.d && m == x.m && y == x.y; }
};
struct Record { Date d; int c; };
vector <Record> r;

bool Leap(int year) {
	if (year % 4) return 0;
	if (year % 400 == 0) return 1;
	return year % 100;
}

Date Tomorrow(Date date) {
	date.d++;
	int bound = (date.m == 2 && Leap(date.y)) ? 29 : DAYS[date.m];
	if (date.d > bound) {
		date.d = 1;
		date.m++;
		if (date.m > 12) {
			date.m = 1;
			date.y++;
		}
	}
	return date;
}

void Process() {
	int n;
	while (cin >> n, n) {
		int ans = 0;
		ll sum = 0;
		r.resize(n);
		for (int i = 0; i < n; i++) cin >> r[i].d.d >> r[i].d.m >> r[i].d.y >> r[i].c;
		for (int i = 0; i < n - 1; i++) {
			if (Tomorrow(r[i].d) == r[i + 1].d) {
				ans++;
				sum += (r[i + 1].c - r[i].c);
			}
		}
		cout << ans << " " << sum << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}