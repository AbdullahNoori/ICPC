/**
 * @file 03.generate_all_subsets.cpp
 * @brief Enumerate all subsets using recursion and bitmasks.
 * @complexity O(2^N * N).
 * @usage
 *   auto subsets = generate_subsets(n);
 * @related 8.misc/01.bit_manipulation_tricks.cpp
 * @related 7.dynamic-programming/01.knapsack_01.cpp
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generate_subsets_recursive(int n) {
    vector<vector<int>> res;
    vector<int> curr;
    function<void(int)> dfs = [&](int k) {
        if (k == n) {
            res.push_back(curr);
            return;
        }
        dfs(k + 1);
        curr.push_back(k);
        dfs(k + 1);
        curr.pop_back();
    };
    dfs(0);
    return res;
}

vector<vector<int>> generate_subsets_bitmask(int n) {
    vector<vector<int>> res;
    res.reserve(1 << n);
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<int> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                subset.push_back(i);
        res.push_back(move(subset));
    }
    return res;
}

#ifdef RUN_EXAMPLE
int main() {
    auto subsets = generate_subsets_recursive(3);
    for (auto& s : subsets) {
        for (int x : s) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
#endif
