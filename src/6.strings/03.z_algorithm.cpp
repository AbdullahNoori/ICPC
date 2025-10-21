/**
 * @file 03.z_algorithm.cpp
 * @brief Z-function for pattern matching and string processing.
 * @complexity O(N).
 * @usage
 *   auto z = z_function(s);
 *   // For pattern search: compute on pattern + '#' + text.
 * @related 6.strings/02.kmp_prefix_function.cpp
 * @related 7.dynamic-programming/02.longest_increasing_subsequence.cpp
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
    int n = static_cast<int>(s.size());
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    z[0] = n;
    return z;
}

#ifdef RUN_EXAMPLE
int main() {
    string s = "aabcaabxaaaz";
    auto z = z_function(s);
    for (int v : z) cout << v << ' ';
    cout << "\n";
    string pattern = "aba", text = "abacaba";
    string combined = pattern + "#" + text;
    auto zz = z_function(combined);
    for (int i = pattern.size() + 1; i < (int)combined.size(); ++i)
        if (zz[i] >= (int)pattern.size())
            cout << "match at " << i - pattern.size() - 1 << "\n";
    return 0;
}
#endif
