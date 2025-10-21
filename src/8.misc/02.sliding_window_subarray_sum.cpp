/**
 * @file 02.sliding_window_subarray_sum.cpp
 * @brief Two-pointer window to find subarray with given sum in non-negative array.
 * @complexity O(N).
 * @usage
 *   auto seg = find_subarray_with_sum(arr, target);
 * @related 7.dynamic-programming/03.max_profit_k_transactions.cpp
 * @related 8.misc/03.generate_all_subsets.cpp
 */

#include <bits/stdc++.h>
using namespace std;

pair<int, int> find_subarray_with_sum(const vector<int>& a, int target) {
    int n = static_cast<int>(a.size());
    int l = 0;
    long long sum = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (l <= r && sum > target) {
            sum -= a[l++];
        }
        if (sum == target) return {l, r};
    }
    return {-1, -1};
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> a = {1, 3, 2, 5, 1, 1, 2, 3};
    auto seg = find_subarray_with_sum(a, 8);
    cout << seg.first << " " << seg.second << "\n"; // 2 4 (2+5+1)
    return 0;
}
#endif
