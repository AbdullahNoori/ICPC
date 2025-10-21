/**
 * @file 02.kmp_prefix_function.cpp
 * @brief Prefix-function (pi array) for Knuth-Morris-Pratt string matching.
 * @complexity O(N).
 * @usage
 *   auto pi = prefix_function(pattern);
 *   auto matches = kmp_search(pattern, text);
 * @related 6.strings/03.z_algorithm.cpp
 * @related 8.misc/03.generate_all_subsets.cpp
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = static_cast<int>(s.size());
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(const string& pat, const string& text) {
    string combined = pat + "#" + text;
    auto pi = prefix_function(combined);
    vector<int> matches;
    int m = pat.size();
    for (int i = m + 1; i < (int)combined.size(); ++i) {
        if (pi[i] == m) matches.push_back(i - 2 * m);
    }
    return matches;
}

#ifdef RUN_EXAMPLE
int main() {
    string pattern = "aba";
    string text = "abacaba";
    auto matches = kmp_search(pattern, text);
    for (int idx : matches) {
        cout << "match at " << idx << "\n";
    }
    return 0;
}
#endif
