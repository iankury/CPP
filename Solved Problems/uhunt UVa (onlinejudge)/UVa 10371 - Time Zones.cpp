#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef pair<int, int> ii;
typedef vector<int> vi;

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

map<string, int> FROM_UTC{
{"UTC", 0},{"GMT", 0},{"BST", 60},
{"IST", 60},{"WET", 0},{"WEST", 60},
{"CET", 60},{"CEST", 120},{"EET", 120},
{"EEST", 180},{"MSK", 180},{"MSD", 240},
{"AST", -240},{"ADT", -180},{"NST", -210},
{"NDT", -150},{"EST", -300},{"EDT", -240},
{"CST", -360},{"CDT", -300},{"MST", -420},
{"MDT", -360},{"PST", -480},{"PDT", -420},
{"HST", -600},{"AKST", -540},{"AKDT", -480},
{"AEST", 600},{"AEDT", 660},{"ACST", 570},
{"ACDT", 630},{"AWST", 480} };

int To_Min(const string& s) { 
	int minutes = s.length() == 5 ? stoi(s.substr(3, 2)) : stoi(s.substr(2, 2));
	return stoi(s.substr(0, 2)) * 60 + minutes; 
}

string Format_Time(int minutes, bool am) {
	if (minutes == 720) return am ? "midnight" : "noon";
	string ans;
	ans.append(to_string(minutes / 60));
	ans.push_back(':');
	if (minutes % 60 < 10) ans.push_back('0');
	ans.append(to_string(minutes % 60));
	ans.append(am ? " a.m." : " p.m.");
	return ans;
}

void Change_am(bool& am, int t, int delta) {
	if (!delta) return;
	t %= 720;
	int d;
	if (delta > 0) {
		d = 719 - t;
		if (delta > d) am = !am;
	}
	else {
		d = (-1) * t;
		if (delta < d) am = !am;
	}
}

void Process() {
	string s, origin, target;
	cin >> s;
	int time, utc, delta;
	bool am;
	if (s == "noon") {
		time = 720;
		am = 0;
	}
	else if (s == "midnight") {
		time = 720;
		am = 1;
	}
	else {
		time = To_Min(s);
		cin >> s;
		am = s[0] == 'a';
	}
	cin >> origin >> target;
	delta = (-1) * FROM_UTC[origin];
	Change_am(am, time, delta);
	time += delta;
	if (time < 60) time += 720;
	else if (time > 779) time -= 720;
	delta = FROM_UTC[target];
	Change_am(am, time, delta);
	time += delta;
	if (time < 60) time += 720;
	else if (time > 779) time -= 720;
	cout << Format_Time(time, am) << "\n";
}

int main() {
	FASTIO();

	int T = 1;
	cin >> T;
	while (T--) Process();

	return 0;
}