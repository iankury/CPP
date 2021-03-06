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

struct Phrase {
	vector<string> words;
	short freq[26], sz;
	Phrase() : sz(0) { for (int i = 0; i < 26; i++) freq[i] = 0; }
	Phrase(Phrase* p) {
		sz = p->sz;
		for (int i = 0; i < 26; i++) freq[i] = p->freq[i];
		words = p->words;
	}
	void Add(const string& r) {
		for (int i = 0; i < r.length(); i++)
			freq[r[i] - 'A']++;
		words.push_back(r);
		sz += r.length();
	}
};

struct Word {
	string s;
	short freq[26], sz;
	Word(const string& r) : s(r) {
		for (int i = 0; i < 26; i++) freq[i] = 0;
		for (int i = 0; i < r.length(); i++)
			freq[r[i] - 'A']++;
		sz = r.length();
	}
};
vector<Word> dic;
vector<Phrase> poss;
vector<string> words_in_order;
Phrase phrase;

void Traverse(int k, Phrase* p) {
	if (k >= dic.size()) return;
	if (dic[k].sz + p->sz > phrase.sz) Traverse(k + 1, p);
	else {
		for (int i = 0; i < 26; i++) {
			if (dic[k].freq[i] + p->freq[i] > phrase.freq[i]) {
				Traverse(k + 1, p);
				return;
			}
		}
		Traverse(k + 1, p);
		Phrase* new_p = new Phrase(p);
		new_p->Add(dic[k].s);
		if (new_p->sz == phrase.sz) {
			for (int i = 0; i < new_p->words.size(); i++) {
				if (binary_search(words_in_order.begin(), words_in_order.end(), new_p->words[i])) {
					return;
				}
			}
			poss.push_back(*new_p);
		}
		else Traverse(k + 1, new_p);
	}
}

void Process() {
	string s;
	while (cin >> s, s != "#") dic.push_back(Word(s));
	cin.ignore();
	while (getline(cin, s), s != "#") {
		phrase = Phrase();
		for (int i = 0; i < s.length(); i++) {
			string temp;
			while (isalpha(s[i])) {
				temp.push_back(s[i]);
				i++;
			}
			phrase.Add(temp);
		}
		words_in_order.clear();
		words_in_order = phrase.words;
		sort(words_in_order.begin(), words_in_order.end());
		poss.clear();
		Traverse(0, new Phrase());
		for (vector<Phrase>::reverse_iterator itr = poss.rbegin(); itr < poss.rend(); itr++) {
			cout << s << " = ";
			for (int i = 0; i < itr->words.size() - 1; i++) cout << itr->words[i] << " ";
			cout << itr->words[itr->words.size() - 1] << "\n";
		}
	}
}

int main() {
	FASTIO();

	int T = 1;
	//cin >> T;
	while (T--) Process();

	return 0;
}