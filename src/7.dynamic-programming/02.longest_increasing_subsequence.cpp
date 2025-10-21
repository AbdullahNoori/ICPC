/**
 * @file 02.longest_increasing_subsequence.cpp
 * @brief Patience sorting style LIS in O(N log N).
 * @complexity O(N log N).
 * @usage
 *   int len = lis_length(sequence);
 * @related 5.math/03.inversion_count_fenwick.cpp
 * @related 7.dynamic-programming/04.coin_change_min_coins.cpp
 */

#include <bits/stdc++.h>
using namespace std;

template <class T>
int lis_length(const vector<T>& a) {
    vector<T> tail;
    for (const T& x : a) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return static_cast<int>(tail.size());
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> seq = {6, 2, 5, 1, 7, 4, 8, 3};
    cout << lis_length(seq) << "\n"; // 4
    return 0;
}
#endif
