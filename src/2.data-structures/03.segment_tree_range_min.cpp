/**
 * @file 03.segment_tree_range_min.cpp
 * @brief Segment tree for range minimum queries with point updates.
 * @complexity Build O(N), query/update O(log N).
 * @usage
 *   SegmentTree<int> st(values, [](int a, int b){return min(a, b);}, INT_MAX);
 *   st.update(pos, new_value);
 *   auto ans = st.query(l, r);
 * @related 7.dynamic-programming/03.max_profit_k_transactions.cpp
 * @related 8.misc/02.sliding_window_subarray_sum.cpp
 */

#include <bits/stdc++.h>
using namespace std;

template <class T, class F>
struct SegmentTree {
    int n = 0;
    F combine;
    T identity;
    vector<T> tree;

    SegmentTree() = default;
    SegmentTree(const vector<T>& a, F combine, T identity)
        : combine(combine), identity(identity) {
        build(a);
    }

    void init(int n_) {
        n = 1;
        while (n < n_) n <<= 1;
        tree.assign(2 * n, identity);
    }

    void build(const vector<T>& a) {
        init(static_cast<int>(a.size()));
        for (int i = 0; i < (int)a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int pos, T value) {
        pos += n;
        tree[pos] = value;
        while (pos >>= 1) tree[pos] = combine(tree[pos << 1], tree[pos << 1 | 1]);
    }

    T query(int l, int r) const {
        T left = identity, right = identity;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) left = combine(left, tree[l++]);
            if (!(r & 1)) right = combine(tree[r--], right);
        }
        return combine(left, right);
    }
};

#ifdef RUN_EXAMPLE
int main() {
    vector<int> a = {5, 2, 6, 3, 9, 1};
    SegmentTree<int, function<int(int, int)>> st(
        a, [](int x, int y) { return min(x, y); }, INT_MAX);
    cout << st.query(1, 4) << "\n"; // minimum on [1,4] -> 2
    st.update(3, 0);
    cout << st.query(0, 5) << "\n"; // minimum on [0,5] -> 0
    return 0;
}
#endif
