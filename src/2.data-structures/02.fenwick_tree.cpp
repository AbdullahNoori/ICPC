/**
 * @file 02.fenwick_tree.cpp
 * @brief Fenwick Tree / Binary Indexed Tree for point updates & prefix queries.
 * @complexity O(log N) per update/query, O(N) build.
 * @usage
 *   Fenwick<long long> fw(n);
 *   fw.add(idx, delta);
 *   auto pref = fw.sum_prefix(r);
 *   auto range = fw.sum_range(l, r);
 * @related 5.math/03.inversion_count_fenwick.cpp
 * @related 7.dynamic-programming/04.coin_change_min_coins.cpp
 */

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Fenwick {
    int n = 0;
    vector<T> bit;

    Fenwick() = default;
    explicit Fenwick(int n) { init(n); }
    explicit Fenwick(const vector<T>& a) { build(a); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, T{});
    }

    void build(const vector<T>& a) {
        init(static_cast<int>(a.size()));
        for (int i = 0; i < n; ++i) add(i + 1, a[i]);
    }

    // add delta at 1-indexed position idx
    void add(int idx, T delta) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += delta;
    }

    // prefix sum [1..idx]
    T sum_prefix(int idx) const {
        T res{};
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }

    // sum over [l..r], 1-indexed
    T sum_range(int l, int r) const {
        if (l > r) return T{};
        return sum_prefix(r) - sum_prefix(l - 1);
    }

    // find smallest index such that prefix >= target (for non-negative deltas)
    int lower_bound(T target) const {
        if (target <= T{}) return 1;
        int idx = 0;
        int bit_mask = 1 << (31 - __builtin_clz(n ? n : 1));
        for (int step = bit_mask; step; step >>= 1) {
            int next = idx + step;
            if (next <= n && bit[next] < target) {
                target -= bit[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};

#ifdef RUN_EXAMPLE
int main() {
    vector<int> arr = {5, 1, 3, 7, 2};
    Fenwick<int> fw(arr.size());
    for (int i = 0; i < (int)arr.size(); ++i) fw.add(i + 1, arr[i]);
    cout << fw.sum_range(2, 4) << "\n"; // 1+3+7 = 11
    fw.add(3, 4);                       // arr[2] += 4
    cout << fw.sum_prefix(4) << "\n";   // 5+1+7+7 = 20
    cout << fw.lower_bound(10) - 1 << "\n"; // 0-based index of prefix >= 10
    return 0;
}
#endif
