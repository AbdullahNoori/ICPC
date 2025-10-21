/**
 * @file 03.max_profit_k_transactions.cpp
 * @brief Stock profit with at most K transactions using DP with rolling arrays.
 * @complexity O(K * N).
 * @usage
 *   long long best = max_profit_with_k_transactions(prices, k);
 * @related 7.dynamic-programming/01.knapsack_01.cpp
 * @related 8.misc/02.sliding_window_subarray_sum.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long max_profit_with_k_transactions(const vector<int>& prices, int k) {
    if (prices.empty() || k == 0) return 0;
    int n = static_cast<int>(prices.size());
    if (k >= n / 2) { // unlimited transactions
        long long greed = 0;
        for (int i = 1; i < n; ++i)
            if (prices[i] > prices[i - 1])
                greed += prices[i] - prices[i - 1];
        return greed;
    }
    vector<long long> best(n, 0), curr(n, 0);
    for (int t = 1; t <= k; ++t) {
        long long max_diff = -prices[0];
        for (int d = 1; d < n; ++d) {
            curr[d] = max(curr[d - 1], prices[d] + max_diff);
            max_diff = max(max_diff, best[d] - prices[d]);
        }
        best.swap(curr);
    }
    return best.back();
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> prices = {5, 11, 3, 50, 60, 90};
    cout << max_profit_with_k_transactions(prices, 2) << "\n"; // 93
    return 0;
}
#endif
