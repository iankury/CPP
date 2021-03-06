#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100003;

int DecToBase (int x, int b) { // b is target base (b < 10)
	int result = 0, mul = 1;
	while (x) {
		result += (x % b)*mul;
		mul *= 10;
		x /= b;
	}
	return result;
}

int main() {
	FASTIO();
	
	return 0;
}

/*
void DEBUG() {
	cout << "DEBUG:\n";
	
	cout << "END OF DEBUG\n";
}
//*/