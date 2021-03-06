#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 1e6 + 3;
int d[N]; // d[i] = menor primo que divide i

void Sieve() {
	memset(d, 0, sizeof d);
	for (int i = 2; i*i < N; i++) {
		if (!d[i]) {
			d[i] = i;
			for (int j = 2 * i; j < N; j += i)
				if (!d[j]) d[j] = i;
		}
	}
	for (int i = 0; i < N; i++) if (!d[i]) d[i] = i;
}

struct Fator {
	int primo, potencia;
	Fator(int x, int y) : primo(x), potencia(y) {}
};

class Fatoracao {
	vector<Fator> fatores;
	int product, ct, n;
	int BinSearch(const int &key, int start, int end) {
		if (start > end) return -1;
		int mid = start + (end - start) / 2;
		if (fatores[mid].primo == key) return mid;
		if (fatores[mid].primo > key) return BinSearch(key, start, mid - 1);
		return BinSearch(key, mid + 1, end);
	}
public:
	Fatoracao(int x) : product(-1), ct(0), n(x) {
		while (x > 1) {
			if (BinSearch(d[x], 0, fatores.size() - 1) < 0) fatores.push_back(Fator(d[x], 1));
			else fatores[fatores.size() - 1].potencia++;
			x /= d[x];
		}
	}
	bool Prime() { return d[n] == n; }
	int Product() {
		if (product < 0) {
			product = 1;
			for (int i = 0; i < fatores.size(); i++)
				product *= fatores[i].primo;
		}
		return product;
	}
	int NextPower() {
		if (ct == fatores.size()) {
			ct = 0;
			return 0;
		}
		ct++;
		return fatores[ct - 1].potencia;
	}
	void Print() {
		cout << "Fatores primos de " << n << ":\n";
		for (int i = 0; i < fatores.size(); i++) {
			cout << fatores[i].primo << "^" << fatores[i].potencia;
			if (i % 15 == 0) cout << "\n";
			else if (i < fatores.size() - 1) cout << ", ";
		}
		cout << "\n";
	}
};

int NextPowerOfTwo(int q) {
	for (int i = 1; i < 31; i++) {
		int wee = (1 << i);
		if (q == wee) return 0;
		else if (q < wee) return wee;
	}
}

int CountRoots (int q) {
	int ans = 0;
	while (q > 1) {
		ans++;
		q /= 2;
	}
	return ans;
}

void Process() {	
	Sieve();
	int x, n, bonus, maxPower;
	x = bonus = maxPower = 0;
	cin >> n;
	Fatoracao f(n);
	if (f.Product() == n) cout << n << " 0\n";
	else {
		while (x = f.NextPower()) {
			int pot = NextPowerOfTwo(x);
			if (pot) bonus = 1;
			else pot = x;
			if (maxPower) {
				if (maxPower != pot) {
					bonus = 1;
					maxPower = maxPower < pot ? pot : maxPower;
				}
			}
			else maxPower = pot;
		}
		cout << f.Product() << " " << CountRoots(maxPower) + bonus << "\n";
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

	cout << "END OF DEBUG\n";
}
//*/