#include <algorithm>
#include "../include/common.h"

// The demons had captured the princess (P) and imprisoned her in the
// bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
// out in a 2D grid. Our valiant knight (K) was initially positioned in the
// top-left room and must fight his way through the dungeon to rescue the
// princess.

// The knight has an initial health point represented by a positive integer. If
// at any point his health point drops to 0 or below, he dies immediately.

// Some of the rooms are guarded by demons, so the knight loses health (negative
// integers) upon entering these rooms; other rooms are either empty (0's) or
// contain magic orbs that increase the knight's health (positive integers).

// In order to reach the princess as quickly as possible, the knight decides to
// move only rightward or downward in each step.

// Write a function to determine the knight's minimum initial health so that he
// is able to rescue the princess.

// For example, given the dungeon below, the initial health of the knight must
// be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

//-2 (K)  -3  3
//-5  -10 1
// 10  30  -5 (P)

// Notes:

// The knight's health has no upper bound.
// Any room can contain threats or power-ups, even the first room the knight
// enters and the bottom-right room where the princess is imprisoned.

#define MAX(x, y) std::max((x), (y))
#define MIN(x, y) std::min((x), (y))
using std::vector;
int min_hp_to_survive(const vector<vector<int> >& dungeon) {
  size_t M = dungeon.size();
  size_t N = dungeon[0].size();
  vector<vector<int> > hp(M, vector<int>(N));
  // dynamic programming resursion formulat: hp(i,j) = max{1,
  // min{hp(i+1,j),hp(i,j+1)}-dungeon(i,j)}
  hp[M - 1][N - 1] = MAX(1, 1 - dungeon[M - 1][N - 1]);
  // init bottom row of hp table
  for (int j = N - 2; j > -1; j--) {
    hp[M - 1][j] = MAX(1, hp[M - 1][j + 1] - dungeon[M - 1][j]);
  }
  // init right-most column
  for (int i = M - 2; i > -1; i--) {
    hp[i][N - 1] = MAX(1, hp[i + 1][N - 1] - dungeon[i][N - 1]);
  }
  // compute diagnal upwards from bottom
  for (int j = N - 2; j > -1; j--) {
    for (int i = M - 2; i > -1; i--) {
      int down = MAX(1, hp[i + 1][j] - dungeon[i][j]);
      int right = MAX(1, hp[i][j + 1] - dungeon[i][j]);
      hp[i][j] = MIN(down, right);
    }
  }

  return hp[0][0];
}

int main(int argc, char const* argv[]) {
  vector<vector<int> > dungeon = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  int min_hp_actual = min_hp_to_survive(dungeon);
  int min_hp_expected = 7;
  ASSERT(min_hp_expected == min_hp_actual, "expected: %d; actual: %d ",
         min_hp_expected, min_hp_actual);
  return 0;
}
