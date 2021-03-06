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

map<string, int> MONTH {
	{"January", 1}, { "February", 2}, { "March", 3}, { "April", 4}, { "May", 5}, { "June", 6},
	{ "July", 7}, { "August", 8}, { "September", 9}, { "October", 10}, { "November", 11}, { "December", 12}
};
map<int, string> MONTH_TO_STRING{
	{1, "January"}, {2, "February"}, {3, "March"}, {4, "April"}, {5, "May"}, {6, "June"},
	{7, "July"}, {8, "August"}, {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}
};
map<int, int> DAYS{ { 1, 31 }, { 2, 28 }, { 3, 31 }, { 4, 30 }, { 5, 31 }, { 6, 30 },
{ 7, 31 }, { 8, 31 }, { 9, 30 }, { 10, 31 }, { 11, 30 }, { 12, 31} };
int ct;

bool Leap(int year) {
	if (year % 4) return 0;
	if (year % 400 == 0) return 1;
	return year % 100;
}

int Days_in_Month(int month, bool leap) {
	if (leap && month == 2) return 29;
	return DAYS[month];
}

int Days_in_Year(int year) { return Leap(year) ? 366 : 365; }

void Process() {
	int day, month, year, k;
	string s;
	getline(cin, s, '-');
	year = stoi(s);
	getline(cin, s, '-');
	month = MONTH[s];
	cin >> day >> k;
	bool leap = Leap(year);
	int day_of_year = 0;
	for (int i = 1; i < month; i++) day_of_year += Days_in_Month(i, leap);
	day_of_year += day;
	int rem_days_in_year = Days_in_Year(year) - day_of_year;
	while (k > rem_days_in_year) {
		k -= rem_days_in_year + 1;
		day = month = 1;
		year++;
		rem_days_in_year = Days_in_Year(year) - 1;
	}
	while (k) {
		int rem_days_in_month = Days_in_Month(month, Leap(year)) - day;
		if (k <= rem_days_in_month) {
			day += k;
			k = 0;
		}
		else {
			k -= (rem_days_in_month + 1);
			day = 1;
			month++;
		}
	}
	cout << "Case " << ++ct << ": ";
	cout << year << "-" << MONTH_TO_STRING[month] << "-" << (day < 10 ? "0" : "") << day << "\n";
}

int main() {
	FASTIO();
	ct = 0;
	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}