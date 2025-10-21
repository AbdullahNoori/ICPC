/**
 * @file 04.binomial_coefficients_mod.cpp
 * @brief Precomputes factorials and inverse factorials modulo prime MOD.
 * @complexity O(N) preprocessing, O(1) per nCr query.
 * @usage
 *   Comb comb(max_n, MOD);
 *   auto ways = comb.nCr(n, r);
 * @related 5.math/01.modular_exponentiation.cpp
 * @related 7.dynamic-programming/01.knapsack_01.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1 % mod;
    base %= mod;
    while (exp) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

struct Comb {
    int n;
    long long mod;
    vector<long long> fact, inv_fact;

    Comb(int n, long long mod) : n(n), mod(mod), fact(n + 1), inv_fact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
        inv_fact[n] = mod_pow(fact[n], mod - 2, mod);
        for (int i = n; i > 0; --i) inv_fact[i - 1] = inv_fact[i] * i % mod;
    }

    long long nCr(int n_, int r_) const {
        if (r_ < 0 || r_ > n_) return 0;
        return fact[n_] * inv_fact[r_] % mod * inv_fact[n_ - r_] % mod;
    }
};

#ifdef RUN_EXAMPLE
int main() {
    constexpr long long MOD = 1'000'000'007LL;
    Comb comb(1'000'000, MOD);
    cout << comb.nCr(10, 3) << "\n";       // 120
    cout << comb.nCr(1000, 500) << "\n";   // big number mod MOD
    return 0;
}
#endif
