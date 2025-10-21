/**
 * @file 01.convex_hull_monotone_chain.cpp
 * @brief 2D convex hull (Monotone Chain) returning hull in counter-clockwise order.
 * @complexity O(N log N).
 * @usage
 *   auto hull = convex_hull(points);
 * @related 5.math/01.modular_exponentiation.cpp
 * @related 8.misc/03.generate_all_subsets.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> convex_hull(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 1) return pts;

    vector<Point> lower, upper;
    for (const Point& p : pts) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower.back(), p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const Point& p = pts[i];
        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper.back(), p) <= 0)
            upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

#ifdef RUN_EXAMPLE
int main() {
    vector<Point> pts = {{0, 0}, {1, 1}, {2, 2}, {2, 0}, {0, 2}, {1, 2}};
    auto hull = convex_hull(pts);
    for (auto [x, y] : hull) {
        cout << x << ' ' << y << '\n';
    }
    return 0;
}
#endif
