/**
 * @file 01.modular_exponentiation.cpp
 * @brief Fast exponentiation (binary exponentiation) modulo MOD.
 * @complexity O(log exponent).
 * @usage
 *   long long x = mod_pow(base, exp, mod);
 * @related 5.math/04.binomial_coefficients_mod.cpp
 * @related 7.dynamic-programming/02.longest_increasing_subsequence.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    base %= mod;
    long long res = 1 % mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

#ifdef RUN_EXAMPLE
int main() {
    constexpr long long MOD = 1'000'000'007LL;
    cout << mod_pow(2, 10, MOD) << "\n"; // 1024
    cout << mod_pow(5, 0, MOD) << "\n";  // 1
    cout << mod_pow(123456789, 1234567, MOD) << "\n";
    return 0;
}
#endif
