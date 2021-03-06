#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

vector<string> NOTES{ "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

string Next_Note(const string& note, int steps) {
	auto itr = lower_bound(NOTES.begin(), NOTES.end(), note);
	for (int i = 0; i <= steps; i++) {
		itr++;
		if (itr == NOTES.end()) itr = NOTES.begin();
	}
	return *itr;
}

void Format(string& s) {
	for (int i = 0; i < s.length(); i++)
		if (isalpha(s[i])) s[i] = toupper(s[i]);
	if (s == "BB") s = "A#";
	else if (s == "DB") s = "C#";
	else if (s == "GB") s = "F#";
	else if (s == "AB") s = "G#";
	else if (s == "EB") s = "D#";
}

string Chord(const vector<string>& s) {
	if (s[1] == Next_Note(s[0], 3) && s[2] == Next_Note(s[1], 2))
		return s[0] + " Major";
	else if (s[1] == Next_Note(s[0], 2) && s[2] == Next_Note(s[1], 3))
		return s[0] + " Minor";
	return "";
}

void Process() {
	vector<string> s;
	s.resize(3);
	while (cin >> s[0] >> s[1] >> s[2]) {
		for (int i = 0; i < 3; i++) {
			cout << s[i] << " ";
			Format(s[i]);
		}
		sort(s.begin(), s.end());
		bool found = 0;
		do {
			string ans = Chord(s);
			if (ans != "") {
				found = 1;
				cout << "is a " << ans << " chord.\n";
			}
		} while (!found && next_permutation(s.begin(), s.end()));
		if (!found) cout << "is unrecognized.\n";
		cin.ignore();
		if (!isalpha(cin.peek())) break;
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}