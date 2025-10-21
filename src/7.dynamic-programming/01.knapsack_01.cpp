/**
 * @file 01.knapsack_01.cpp
 * @brief 0/1 knapsack with value maximisation (space optimised).
 * @complexity O(N * W).
 * @usage
 *   long long best = knapsack_01(weights, values, capacity);
 * @related 7.dynamic-programming/03.max_profit_k_transactions.cpp
 * @related 2.data-structures/03.segment_tree_range_min.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long knapsack_01(const vector<int>& weights,
                      const vector<long long>& values,
                      int capacity) {
    vector<long long> dp(capacity + 1, 0);
    for (size_t i = 0; i < weights.size(); ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> weights = {1, 3, 4, 5};
    vector<long long> values = {1, 4, 5, 7};
    cout << knapsack_01(weights, values, 7) << "\n"; // 9
    return 0;
}
#endif
