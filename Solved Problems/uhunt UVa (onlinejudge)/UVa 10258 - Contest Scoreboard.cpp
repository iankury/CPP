#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>
#include <sstream>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007;

bool virgin;

bool Is_Blank(const string& s) {
	for (int i = 0; i < s.length(); i++) if (!isblank(s[i])) return 0;
	return 1;
}

struct Submission {
	bool correct;
	int time;
	bool operator < (const Submission& sub) const { return time < sub.time; }
};

struct Problem {
	bool solved;
	vector<Submission> submissions;
	Problem() : solved(0) {}
	void Sort() { sort(submissions.begin(), submissions.end()); }
	int Time() {
		int ans = 0;
		for (auto& x : submissions) {
			if (x.correct) {
				ans += x.time;
				break;
			}
			ans += 20;
		}
		return ans;
	}
};

struct Contestant {
	bool alive;
	int key, solved, penalty;
	map<int, Problem> problems;
	Contestant() : alive(0), penalty(0), solved(0) {}
	void Get_Score() {
		for (auto& x : problems) {
			if (x.second.solved) {
				solved++;
				x.second.Sort();
				penalty += x.second.Time();
			}
		}
	}
	bool operator < (const Contestant& cont) const {
		if (solved == cont.solved)
			return (penalty == cont.penalty) ? key < cont.key : penalty < cont.penalty;
		return solved > cont.solved;
	}
};

void Process() {
	if (virgin) virgin = 0;
	else cout << "\n";
	string s;
	vector<Contestant> a;
	a.resize(101);
	for (int i = 0; i < a.size(); i++) a[i].key = i;
	while (!cin.eof() && getline(cin, s)) {
		if (Is_Blank(s)) break;
		stringstream ss(s);
		int cont, prob, time;
		char c;
		ss >> cont >> prob >> time >> c;
		a[cont].alive = 1;
		if (c == 'C' || c == 'I') {
			if (a[cont].problems.find(prob) == a[cont].problems.end())
				a[cont].problems[prob] = Problem();
			if (c == 'C') a[cont].problems[prob].solved = 1;
			a[cont].problems[prob].submissions.push_back({ c == 'C', time });
		}
	}
	for (auto& x : a) if (x.alive) x.Get_Score();
	sort(a.begin(), a.end());
	for (auto& x : a) if (x.alive) cout << x.key << " " << x.solved << " " << x.penalty << "\n";
}

int main() {
	FASTIO();

	virgin = 1;
	int T = 1;
	cin >> T;
	cin.ignore();
	string s;
	getline(cin, s);
	while (T--) Process();

	return 0;
}