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

struct Max {
	int max_freq;
	vector<string> names;
	Max() : max_freq(0) {}
	void Update(int& x, const string& s) {
		x++;
		if (x > max_freq) {
			names.clear();
			names.push_back(s);
			max_freq = x;
		}
		else if (x == max_freq) names.push_back(s);
	}
	void Zero(string& s) { if (!max_freq) names.push_back(s); }
};

void Process() {
	int n, k;
	Max Pizza, Taxi, Girls;
	cin >> n;
	while (n--) {
		cin >> k;
		string name;
		cin >> name;
		int p = 0, t = 0, g = 0;
		Pizza.Zero(name);
		Taxi.Zero(name);
		Girls.Zero(name);
		while (k--) {
			string s;
			cin >> s;
			bool taxi = 1, pizza = 1;
			char digits[]{ s[0], s[1], s[3], s[4], s[6], s[7] };
			
			for (int i = 1; i < 6; i++) {
				if (digits[i] != digits[i - 1]) taxi = 0;
				if (digits[i] >= digits[i - 1]) pizza = 0;
			}
			if (pizza) Pizza.Update(p, name);
			else if (taxi) Taxi.Update(t, name);
			else Girls.Update(g, name);
		}
	}
	for (int i = 0; i < 3; i++) {
		Max& current = Taxi;
		switch (i) {
		case 1:
			cout << "If you want to order a pizza, you should call: ";
			current = Pizza;
			break;
		case 2:
			cout << "If you want to go to a cafe with a wonderful girl, you should call: ";
			current = Girls;
			break;
		default:
			cout << "If you want to call a taxi, you should call: ";
		}
		if (current.names.size()) cout << current.names[0];
		for (int i = 1; i < current.names.size(); i++) {
			cout << ", ";
			cout << current.names[i];
		}
		cout << ".\n";
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}


/*
void DEBUG() {
	cout << "DEBUG" << ":\n";
	cout << "Printing digits:\n";
			for (int i = 1; i < 6; i++) {
				cout << digits[i] << "\n";
			}
	cout << "END OF DEBUG\n";
}
//*/