#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iterator>
#include <ctype.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

vector<string> scales[12];
const int MAJOR[]{ 0, 2, 4, 5, 7, 9, 11 };

map<string, int> decode{ { "SECOND", 1 }, { "THIRD", 2 }, { "FOURTH", 3 }, { "FIFTH", 4 },
{ "SIXTH", 5 }, { "SEVENTH", 6 }, { "OCTAVE", 7 }, { "UP", 1 }, { "DOWN", -1 },
{ "C", 0 }, { "B#", 0 }, { "C#", 1 }, { "Db", 1 }, { "D", 2 }, { "D#", 3 },
{ "Eb", 3 }, { "E", 4 }, { "Fb", 4 }, { "F", 5 }, { "E#", 5 }, { "F#", 6 },
{ "Gb", 6 }, { "G", 7 }, { "G#", 8 }, { "Ab", 8 }, { "A", 9 }, { "A#", 10 },
{ "Bb", 10 }, { "B", 11 }, { "Cb", 11 } };

map<int, vector<string>> encode{ { 0, { "C", "B#"} }, { 1, {"C#", "Db"} },
{ 2, {"D", "D"} }, { 3, {"D#", "Eb"} }, { 4, {"E", "Fb"} }, { 5, {"F", "E#"} },
{ 6, {"F#", "Gb"} }, { 7, {"G", "G"} }, { 8, {"G#", "Ab"} }, { 9, {"A", "A"} },
{ 10, {"A#", "Bb"} }, { 11, {"B", "Cb"} } };

bool Bemol(const string& s) {
	if (s.length() < 2) return 0;
	return s[1] == 'b';
}

bool Sust(const string& s) {
	if (s.length() < 2) return 0;
	return s[1] == '#';
}

bool Repeated(const string& s, const vector<string>& v) {
	for (auto& x : v) if (x[0] == s[0]) return 1;
	return 0;
}

void Build_Scale(const string& s) {
	bool forbid_b = Sust(s), forbid_s = Bemol(s);
	int first = decode[s];
	for (int i = 0; i < 7; i++) {
		int note = first + MAJOR[i];
		if (note > 11) note -= 12;
		else if (note < 0) note += 12;
		string a = encode[note][0], b = encode[note][1];
		if (forbid_b && Bemol(a)) scales[first].push_back(b);
		else if (forbid_b && Bemol(b)) scales[first].push_back(a);
		else if (forbid_s && Sust(a)) scales[first].push_back(b);
		else if (forbid_s && Sust(b)) scales[first].push_back(a);
		else {
			if (Repeated(a, scales[first])) {
				if (Bemol(b)) forbid_s = 1;
				else if (Sust(b)) forbid_b = 1;
				scales[first].push_back(b);
			}
			else if (Repeated(b, scales[first])) {
				if (Bemol(a)) forbid_s = 1;
				else if (Sust(a)) forbid_b = 1;
				scales[first].push_back(a);
			}
			else if (a.length() > b.length()) {
				if (Bemol(b)) forbid_s = 1;
				else if (Sust(b)) forbid_b = 1;
				scales[first].push_back(b);
			}
			else {
				if (Bemol(a)) forbid_s = 1;
				else if (Sust(a)) forbid_b = 1;
				scales[first].push_back(a);
			}
		}
	}
}

void Build_All() {
	for (int i = 0; i < 12; i++) {
		string a = encode[i][0], b = encode[i][1];
		if (a.length() == 1) Build_Scale(a);
		else if (b.length() == 1) Build_Scale(b);
		else if (Sust(a)) Build_Scale(b);
		else Build_Scale(a);
	}
}

int Get_Index(const string& note, int scale) {
	for (int i = 0; i < 7; i++) if (scales[scale][i] == note) return i;
	return -1;
}

void Process() {
	Build_All();
	string r, s;
	char buffer[25];
	while (getline(cin, r)) {
		getline(cin, s);
		cout << "Key of " << r << "\n";
		istringstream iss(s);
		char buffer[25];
		string w[3];
		int turn = 0;
		while (iss.getline(buffer, 25, ';')) {
			istringstream iss2(buffer);
			iss2 >> w[0] >> w[1] >> w[2];
			int scale = decode[r], dir = decode[w[1]], dist = decode[w[2]];
			int ind = Get_Index(w[0], scale);
			cout << w[0] << ": ";
			if (ind == -1) cout << "invalid note for this key\n";
			else {
				cout << w[1] << " " << w[2] << " > ";
				ind += (dist * dir);
				if (ind > 6) ind -= 7;
				else if (ind < 0) ind += 7;
				cout << scales[scale][ind] << "\n";
			}
		}
		cout << "\n";
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