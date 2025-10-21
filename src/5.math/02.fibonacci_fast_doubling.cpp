/**
 * @file 02.fibonacci_fast_doubling.cpp
 * @brief Computes nth Fibonacci number using fast doubling.
 * @complexity O(log n).
 * @usage
 *   auto [fn, fn1] = fibonacci_fast_doubling(n);
 * @related 7.dynamic-programming/05.grid_paths_dp.cpp
 * @related 5.math/04.binomial_coefficients_mod.cpp
 */

#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> fib_pair(long long n) {
    if (n == 0) return {0, 1};
    auto [a, b] = fib_pair(n >> 1);
    long long c = a * (2 * b - a);
    long long d = a * a + b * b;
    if (n & 1) return {d, c + d};
    return {c, d};
}

long long fibonacci(long long n) {
    return fib_pair(n).first;
}

#ifdef RUN_EXAMPLE
int main() {
    for (int n : {0, 1, 2, 5, 10, 20}) {
        cout << "F(" << n << ") = " << fibonacci(n) << "\n";
    }
    return 0;
}
#endif
