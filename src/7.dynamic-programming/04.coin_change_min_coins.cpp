/**
 * @file 04.coin_change_min_coins.cpp
 * @brief Minimum number of coins to form value V with unlimited coins.
 * @complexity O(N * V).
 * @usage
 *   int answers = min_coins(coins, target);
 * @related 2.data-structures/02.fenwick_tree.cpp
 * @related 7.dynamic-programming/05.grid_paths_dp.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int min_coins(const vector<int>& coins, int target) {
    const int INF = 1e9;
    vector<int> dp(target + 1, INF);
    dp[0] = 0;
    for (int v = 1; v <= target; ++v) {
        for (int c : coins) {
            if (v - c >= 0)
                dp[v] = min(dp[v], dp[v - c] + 1);
        }
    }
    return dp[target] == INF ? -1 : dp[target];
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> coins = {1, 3, 4};
    cout << min_coins(coins, 6) << "\n"; // 2 (3+3 or 4+1+1)
    cout << min_coins(coins, 2) << "\n"; // 2 (1+1)
    cout << min_coins(coins, 7) << "\n"; // 2 (3+4)
    return 0;
}
#endif
