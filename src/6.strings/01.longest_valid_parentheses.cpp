/**
 * @file 01.longest_valid_parentheses.cpp
 * @brief Longest valid parentheses substring via stack of indices.
 * @complexity O(N).
 * @usage
 *   int len = longest_valid_parentheses(s);
 * @related 8.misc/02.sliding_window_subarray_sum.cpp
 * @related 6.strings/02.kmp_prefix_function.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int longest_valid_parentheses(const string& s) {
    stack<int> st;
    st.push(-1);
    int best = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i);
            } else {
                best = max(best, i - st.top());
            }
        }
    }
    return best;
}

#ifdef RUN_EXAMPLE
int main() {
    cout << longest_valid_parentheses("(()") << "\n";        // 2
    cout << longest_valid_parentheses(")()())") << "\n";     // 4
    cout << longest_valid_parentheses("()(()))))") << "\n";  // 6
    return 0;
}
#endif
