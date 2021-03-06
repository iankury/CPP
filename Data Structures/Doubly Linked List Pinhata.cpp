#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
#define db if(1)
#define FASTIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

template <typename T> struct Node {
  T x;
  Node* prev, *next;
};

template <typename T> struct List {
  Node<T>* front, *back;
  int sz;
  void Push_Front(const T& _data) {
    if (!sz) {
      Node<T>* p = new Node<T>{ _data, 0, 0 };
      front = back = p;
    }
    else {
      Node<T>* p = new Node<T>{ _data, 0, front };
      front->prev = p;
      front = p;
    }
    sz++;
  }
  void Push_Back(const T& _data) {
    if (!sz) {
      Node<T>* p = new Node<T>{ _data, 0, 0 };
      front = back = p;
    }
    else {
      Node<T>* p = new Node<T>{ _data, back, 0 };
      back->next = p;
      back = p;
    }
    sz++;
  }
  void Pop_Front() {
    if (sz) {
      if (sz == 1) {
        delete front;
        front = back = 0;
      }
      else {
        Node<T>* todel = front;
        front = front->next;
        front->prev = 0;
        delete todel;
      }
      sz--;
    }
  }
  void Pop_Back() {
    if (sz) {
      if (sz == 1) {
        delete back;
        front = back = 0;
      }
      else {
        Node<T>* todel = back;
        back = back->prev;
        back->next = 0;
        delete todel;
      }
      sz--;
    }
  }
  T& Front() {
    return front->x;
  }
  T& Back() {
    return back->x;
  }
  void Erase(Node<T>* p) {
    if (p) {
      if (p == front)
        Pop_Front();
      else if (p == back)
        Pop_Back();
      else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        sz--;
      }
    }
  }
  bool Empty() { return !sz; }
  List() : sz(0), front(0), back(0) {}
  List(const T& _node) : sz(0) {
    Push_Back(_node);
  }
  List(const vector<T>& _v) {
    for (const T& _node : _v)
      Push_Back(_node);
  }
  ~List() {
    Node<T>* p = front;
    while (p) {
      Node<T>* todel = p;
      p = p->next;
      delete todel;
    }
  }
};

int main() {
  FASTIO();

  

  return 0;
}