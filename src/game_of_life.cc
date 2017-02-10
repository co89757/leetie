#include <vector>
#include "../include/common.h"

// According to the Wikipedia's article: "The Game of Life, also known simply as
// Life, is a cellular automaton devised by the British mathematician John
// Horton Conway in 1970."

// Given a board with m by n cells, each cell has an initial state live (1) or
// dead (0). Each cell interacts with its eight neighbors (horizontal, vertical,
// diagonal) using the following four rules (taken from the above Wikipedia
// article):

// Any live cell with fewer than two live neighbors dies, as if caused by
// under-population.
// Any live cell with two or three live neighbors lives on to the next
// generation.
// Any live cell with more than three live neighbors dies, as if by
// over-population..
// Any dead cell with exactly three live neighbors becomes a live cell, as if by
// reproduction.
// Write a function to compute the next state (after one update) of the board
// given its current state.

// Follow up:
// Could you solve it in-place? Remember that the board needs to be updated at
// the same time: You cannot update some cells first and then use their updated
// values to update other cells.
// In this question, we represent the board using a 2D array. In principle, the
// board is infinite, which would cause problems when the active area encroaches
// the border of the array. How would you address these problems?

// Analysis: encode each cell with 4 binary states, (DL means dead in this
// state, live in next state)
// DD (0) LL(1) LD(2) DL(3)
using std::vector;
void gameOfLife(vector<vector<int> >& board) {
  int m = board.size();
  int n = m ? board[0].size() : 0;
  int di[8] = {0, -1, -1, -1, 0, 1, 1, 1};
  int dj[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // determine the encoded state of cell (i,j)
      int count = 0;
      for (int k = 0; k < 8; ++k) {
        int r = i + di[k];
        int c = j + dj[k];
        if (r >= 0 && r < m && c >= 0 && c < n &&
            (board[r][c] == 2 || board[r][c] == 1))
          count++;
      }
      int x = board[i][j];
      if (x == 0 && count == 3) {
        board[i][j] = 3;
      } else if (x == 1 && (count < 2 || count > 3))
        board[i][j] = 2;
    }
  }

  // now for each cell, take cell value mod by 2 and derive next state cells
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      board[i][j] &= 0x1;
    }
  }
}

int main(int argc, char const* argv[]) {
  vector<vector<int> > board = {
      {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 1}};

  gameOfLife(board);

  vector<vector<int> > next_board = {
      {0, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT(board[i][j] == next_board[i][j],
             "mismatch at [%d,%d]: actual: [%d], expected:[%d]", i, j,
             board[i][j], next_board[i][j]);
    }
  }

  return 0;
}
