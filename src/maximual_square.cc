#include <algorithm>
#include "../include/common.h"
#define MIN3(x, y, z) std::min(std::min((x), (y)), (z))
using std::vector;
/**** Problem Description https://leetcode.com/problems/maximal-square/
* Given a 2D binary matrix filled with 0's and 1's, find the largest square
containing only 1's and return its area.
*
*For example, given the following matrix:
*
*1 0 1 0 0
*1 0 1 1 1
*1 1 1 1 1
*1 0 0 1 0

Return 4.
***********************************************************************/
int maximalSquare(vector<vector<char> >& matrix) {
  // dynamic programming, recursion formulat: dp[i][j]=
  // min(dp[i][j-1],dp[i-1][j] ,dp[i-1][j-1]) + 1
  int M = matrix.size();
  int N = matrix[0].size();
  vector<vector<int> > dp(M, vector<int>(N));
  int maxl = 0;
  // populate the first column of the dp table
  for (int i = 0; i < M; ++i) {
    int cellval = matrix[i][0] - '0';
    dp[i][0] = cellval;
    maxl = std::max(maxl, cellval);
  }
  // now populate fir)t row
  for (int j = 0; j < N; ++j) {
    dp[0][j] = matrix[0][j] - '0';
    maxl = std::max(maxl, dp[0][j]);
  }

  // the remaining cells
  for (int i = 1; i < M; ++i) {
    for (int j = 1; j < N; ++j) {
      auto a = MIN3(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1;
      dp[i][j] = (matrix[i][j] - '0') == 0 ? 0 : a;
      maxl = std::max(maxl, dp[i][j]);
    }
  }

  return maxl * maxl;
}

int main(int argc, char* argv[]) {
  vector<vector<char> > matrix = {{'1', '0', '1', '0', '0'},
                                  {'1', '0', '1', '1', '1'},
                                  {'1', '1', '1', '1', '1'},
                                  {'1', '0', '0', '1', '0'}};
  int ans = maximalSquare(matrix);
  ASSERT(ans == 4, "actual:%d expected:4", ans);
  return 0;
}
