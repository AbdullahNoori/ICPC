/**
 * @file 03.inversion_count_fenwick.cpp
 * @brief Counts inversions in O(N log N) using Fenwick tree.
 * @complexity O(N log N) after coordinate compression.
 * @usage
 *   long long inv = inversion_count(arr);
 * @related 2.data-structures/02.fenwick_tree.cpp
 * @related 7.dynamic-programming/02.longest_increasing_subsequence.cpp
 */

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Fenwick {
    int n;
    vector<T> bit;
    explicit Fenwick(int n) : n(n), bit(n + 1, T{}) {}
    void add(int idx, T val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    T sum(int idx) const {
        T res{};
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
};

long long inversion_count(vector<int> a) {
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get = [&](int x) {
        return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
    };
    Fenwick<long long> fw(vals.size());
    long long inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        int id = get(a[i]);
        inv += fw.sum(id - 1);
        fw.add(id, 1);
    }
    return inv;
}

#ifdef RUN_EXAMPLE
int main() {
    vector<int> arr = {3, 1, 2, 5, 4};
    cout << inversion_count(arr) << "\n"; // 3 inversions
    return 0;
}
#endif
