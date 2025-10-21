/**
 * @file 01.fast_io_template.cpp
 * @brief Fast input/output helpers and minimal contest template.
 * @complexity Each parsed token is O(1) amortised; output flushing is O(k).
 * @usage
 *   FastIO io;
 *   int n = io.next<int>();
 *   vector<int> a(n);
 *   for (int i = 0; i < n; ++i) a[i] = io.next<int>();
 *   io.print_line(a.back());
 * @related 2.data-structures/01.disjoint_set_union.cpp
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct FastIO {
    static constexpr size_t BUFSIZE = 1 << 16;
    array<char, BUFSIZE> in_buf{}, out_buf{};
    size_t in_len = 0, in_pos = 0, out_pos = 0;

    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }

    ~FastIO() { flush(); }

    inline char read_char() {
        if (in_pos == in_len) {
            in_len = fread(in_buf.data(), 1, BUFSIZE, stdin);
            in_pos = 0;
            if (in_len == 0) return EOF;
        }
        return in_buf[in_pos++];
    }

    template <class T>
    T next() {
        static_assert(is_integral_v<T> || is_floating_point_v<T>,
                      "FastIO::next only supports arithmetic types");
        char c = read_char();
        while (c <= ' ' && c != EOF) c = read_char();
        bool neg = false;
        if constexpr (is_signed_v<T>) {
            if (c == '-') {
                neg = true;
                c = read_char();
            }
        }
        T val = 0;
        if constexpr (is_integral_v<T>) {
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read_char();
            }
            return neg ? -val : val;
        } else {
            long double v = 0, div = 1;
            while (c > ' ' && c != '.' && c != EOF) {
                v = v * 10 + (c - '0');
                c = read_char();
            }
            if (c == '.') {
                c = read_char();
                while (c > ' ') {
                    v = v * 10 + (c - '0');
                    div *= 10;
                    c = read_char();
                }
            }
            v = neg ? -v : v;
            return static_cast<T>(v / div);
        }
    }

    inline void write_char(char c) {
        if (out_pos == BUFSIZE) flush();
        out_buf[out_pos++] = c;
    }

    template <class T>
    void print(const T& value) {
        if constexpr (is_integral_v<T>) {
            if (value == 0) {
                write_char('0');
                return;
            }
            if (value < 0) {
                write_char('-');
                value = -value;
            }
            char tmp[32];
            int len = 0;
            while (value > 0) {
                tmp[len++] = char('0' + value % 10);
                value /= 10;
            }
            while (len--) write_char(tmp[len]);
        } else if constexpr (is_floating_point_v<T>) {
            string s = to_string(value);
            for (char c : s) write_char(c);
        } else if constexpr (is_same_v<T, string> || is_same_v<T, string_view>) {
            for (char c : value) write_char(c);
        } else if constexpr (is_same_v<T, const char*>) {
            for (const char* p = value; *p; ++p) write_char(*p);
        } else if constexpr (is_same_v<T, char>) {
            write_char(value);
        } else {
            static_assert(!sizeof(T), "Unsupported type for FastIO::print");
        }
    }

    template <class... Args>
    void print_line(const Args&... args) {
        if constexpr (sizeof...(Args) == 0) {
            write_char('\n');
        } else {
            ((print(args), write_char(' ')), ...);
            out_buf[out_pos - 1] = '\n';
        }
    }

    void flush() {
        if (out_pos) {
            fwrite(out_buf.data(), 1, out_pos, stdout);
            out_pos = 0;
        }
    }
};

#ifdef RUN_EXAMPLE
int main() {
    FastIO io;
    int n = io.next<int>();
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = io.next<long long>();
    }
    long long sum = accumulate(a.begin(), a.end(), 0LL);
    io.print_line("sum:", sum);
    return 0;
}
#endif
