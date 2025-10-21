/**
 * @file 01.dfs_grid_paths.cpp
 * @brief Enumerate number of monotonic grid paths (right/down moves only).
 * @complexity O(W * H) using memoised DFS.
 * @usage
 *   long long ways = count_grid_paths(4, 3);
 * @related 7.dynamic-programming/05.grid_paths_dp.cpp
 * @related 8.misc/03.generate_all_subsets.cpp
 */

#include <bits/stdc++.h>
using namespace std;

static long long dfs(int x, int y, int w, int h, vector<vector<long long>>& memo) {
    if (x == w - 1 && y == h - 1) return 1;
    auto& res = memo[y][x];
    if (res != -1) return res;
    res = 0;
    if (x + 1 < w) res += dfs(x + 1, y, w, h, memo);
    if (y + 1 < h) res += dfs(x, y + 1, w, h, memo);
    return res;
}

long long count_grid_paths(int w, int h) {
    vector<vector<long long>> memo(h, vector<long long>(w, -1));
    return dfs(0, 0, w, h, memo);
}

#ifdef RUN_EXAMPLE
int main() {
    cout << count_grid_paths(4, 3) << "\n"; // 10
    cout << count_grid_paths(2, 2) << "\n"; // 2
    return 0;
}
#endif
