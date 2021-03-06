#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

int mtd[14], mtdL[14], dim[14], dimL[14];

bool Leap(int year) {
	if (!(year % 4)) {
		if (!(year % 400)) return 1;
		else if (year % 100) return 1;
		else return 0;
	}
	return 0;
}

int DIM(int m, bool leap) {
	if (leap && m == 2) return 29;
	else if (m == 2) return 28;
	else if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
	return 31;
}

void DP() {
	int sum = 0, sumL = 0;
	for (int i = 1; i <= 12; i++) {
		dim[i] = DIM(i, 0), dimL[i] = DIM(i, 1);
		mtd[i] = sum;
		mtdL[i] = sumL;
		sum += dim[i];
		sumL += dimL[i];
	}
}

int YTD(int m, int y) {
	int ans = 0;
	for (int i = 0; i < y; i++) ans += Leap(i) ? 366 : 365;
	return ans;
}

void Process() {
	DP();
	int n, d, m, y, total_days;
	while (cin >> n >> d >> m >> y, y) {
		total_days = d + n + YTD(m, y);
		total_days += Leap(y) ? mtdL[m] : mtd[m];
		y = 0;
		int DIY = 366;
		while (total_days > DIY) {
			total_days -= DIY;
			y++;
			DIY = Leap(y) ? 366 : 365;
		}
		m = 1;
		bool leap = Leap(y);
		int dm = leap ? dimL[m] : dim[m];
		while (total_days > dm) {
			total_days -= dm;
			m++;
			if (m > 12) {
				m = 1;
				y++;
			}
			dm = leap ? dimL[m] : dim[m];
		}
		d = total_days;
		dm = leap ? dimL[m] : dim[m];
		cout << d << " " << m << " " << y << "\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}