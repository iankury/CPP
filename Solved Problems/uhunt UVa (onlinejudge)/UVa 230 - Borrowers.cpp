#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 100005, M = 1000000007, BIG = 0x3f3f3f3f;

int ct = 0;
int n;

enum { SHELF, PENDING, BORROWED };

struct Book {
	string title, author;
	int status;
	bool operator < (const Book& p) const {
		if (author == p.author) return title < p.title;
		return author < p.author;
	}
};
vector<Book> books;
map<string, int> indices;

int main() {
	FASTIO();

	string s;
	while (getline(cin, s), s != "END") {
		Book book;
		int i = 1;
		book.title = "\"";
		while (s[i] != '\"') book.title.push_back(s[i++]);
		book.title.push_back('\"');
		while (s[i++] != 'y') {}
		while (!isblank(s[i++])) {}
		while (i < s.length()) book.author.push_back(s[i++]);
		book.status = SHELF;
		books.push_back(book);
	}
	sort(books.begin(), books.end());
	for (int i = 0; i < books.size(); i++) indices[books[i].title] = i;
	int pending = 0;
	while (getline(cin, s), s != "END") {
		if (s[0] == 'B') {
			int i = 6;
			while (!isblank(s[i++])) {}
			books[indices[s.substr(i)]].status = BORROWED;
		}
		else if (s[0] == 'R') {
			int i = 6;
			while (!isblank(s[i++])) {}
			books[indices[s.substr(i)]].status = PENDING;
			pending++;
		}
		else {
			int neighbor = -1;
			for (int i = 0; i < books.size(); i++) {
				if (books[i].status == PENDING) {
					books[i].status = SHELF;
					pending--;
					if (neighbor == -1) cout << "Put " << books[i].title << " first\n";
					else cout << "Put " << books[i].title << " after " << books[neighbor].title << "\n";
				}
				if (books[i].status == SHELF) neighbor = i;
				if (!pending) break;
			}
			cout << "END\n";
		}
	}

	return 0;
}