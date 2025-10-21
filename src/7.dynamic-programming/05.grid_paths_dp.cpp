/**
 * @file 05.grid_paths_dp.cpp
 * @brief Count number of shortest lattice paths on a grid with obstacles.
 * @complexity O(N * M).
 * @usage
 *   long long ways = count_paths(grid, MOD);
 * @related 3.graphs/01.dfs_grid_paths.cpp
 * @related 8.misc/02.sliding_window_subarray_sum.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long count_paths(const vector<string>& grid, long long mod) {
    int n = grid.size();
    int m = grid.empty() ? 0 : grid[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m, 0));
    if (n == 0 || m == 0 || grid[0][0] == '#') return 0;
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') continue;
            if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
    }
    return dp[n - 1][m - 1];
}

#ifdef RUN_EXAMPLE
int main() {
    vector<string> grid = {
        "...",
        ".#.",
        "..."
    };
    cout << count_paths(grid, 1'000'000'007LL) << "\n"; // 2
    return 0;
}
#endif
