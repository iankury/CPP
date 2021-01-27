#include <bits/stdc++.h>
using namespace std;
void io() { ios_base::sync_with_stdio(0), cin.tie(0); }
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

const vi delta_row{ -2, -1, 1, 2, 2, 1, -1, -2 };
const vi delta_col{ 1, 2, 2, 1, -1, -2, -2, -1 };

int initial_row, initial_col;
vector<vi> board(8, vi(8));

bool InBounds(int i, int j) {
  return i >= 0 && i < 8 && j >= 0 && j < 8;
}

void Print() {
  for (const vi& row : board) {
    for (int x : row)
      cout << x << " ";
    cout << "\n";
  }
}

vector<ii> PossibleMoves(int i, int j) {
  vector<ii> possible_moves;

  for (int k = 0; k < 8; k++) {
    const int ix = i + delta_row[k];
    const int jx = j + delta_col[k];

    if (InBounds(ix, jx) && !board[ix][jx])
      possible_moves.push_back({ ix, jx });
  }

  return possible_moves;
}

void Recur(int i, int j, int move) {
  const int backup = board[i][j];
  board[i][j] = move;

  if (move == 64) {
    Print();
    exit(0);
  }

  vector<ii> possible_moves = PossibleMoves(i, j);

  sort(begin(possible_moves), end(possible_moves), [&](const ii& p, const ii& q) {
    const int p_options = PossibleMoves(p.first, p.second).size();
    const int q_options = PossibleMoves(q.first, q.second).size();
    return p_options < q_options; // Warnsdorf's heuristic
  });

  for (const ii& p : possible_moves)
    Recur(p.first, p.second, move + 1);

  board[i][j] = backup;
}

int main() {
  io();

  cin >> initial_col >> initial_row;

  Recur(initial_row - 1, initial_col - 1, 1);

  return 0;
}