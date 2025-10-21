/**
 * @file 01.bit_manipulation_tricks.cpp
 * @brief Handy bit tricks (set/clear/test, lowbit, popcount).
 * @complexity O(1) per operation.
 * @usage
 *   bool kth = has_kth_bit(x, k);
 *   x = set_bit(x, k);
 * @related 6.strings/01.longest_valid_parentheses.cpp
 * @related 8.misc/03.generate_all_subsets.cpp
 */

#include <bits/stdc++.h>
using namespace std;

bool has_kth_bit(unsigned int x, int k) { return (x >> k) & 1U; }
unsigned int set_bit(unsigned int x, int k) { return x | (1U << k); }
unsigned int clear_bit(unsigned int x, int k) { return x & ~(1U << k); }
unsigned int toggle_bit(unsigned int x, int k) { return x ^ (1U << k); }
unsigned int lowbit(unsigned int x) { return x & -x; }
unsigned int reset_lowbit(unsigned int x) { return x & (x - 1); }
int hamming_distance(unsigned int a, unsigned int b) {
    return __builtin_popcount(a ^ b);
}

#ifdef RUN_EXAMPLE
int main() {
    unsigned int x = 0b101100;
    cout << has_kth_bit(x, 2) << "\n";      // true
    x = set_bit(x, 1);                      // 0b101110
    x = clear_bit(x, 4);                    // 0b001110
    x = toggle_bit(x, 0);                   // 0b001111
    cout << bitset<8>(x) << "\n";
    cout << lowbit(0b11000) << "\n";        // 8
    cout << reset_lowbit(0b11000) << "\n";  // 0b10000
    cout << hamming_distance(0b1010, 0b0110) << "\n"; // 2
    return 0;
}
#endif
