#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a point with its original index
struct Point {
    long long x, y;
    int idx;
};

// Cross product of vectors (p1->p2) x (p1->p3)
long long cross(const Point& p1, const Point& p2, const Point& p3) {
    long long dx1 = p2.x - p1.x;
    long long dy1 = p2.y - p1.y;
    long long dx2 = p3.x - p2.x;
    long long dy2 = p3.y - p2.y;
    return dx1 * dy2 - dy1 * dx2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].idx = i + 1; // 1-based index
    }
    string s;
    cin >> s;

    // Find the leftmost (and then bottommost) point to start
    int start = 0;
    for (int i = 1; i < n; ++i) {
        if (pts[i].x < pts[start].x || (pts[i].x == pts[start].x && pts[i].y < pts[start].y)) {
            start = i;
        }
    }

    vector<bool> used(n, false);
    vector<int> order;
    order.push_back(start);
    used[start] = true;

    // For each turn, select the next point according to the required turn
    for (int i = 0; i < n - 1; ++i) {
        int cur = order.back();
        int nxt = -1;
        // Find the first unused point to initialize
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                nxt = j;
                break;
            }
        }
        // For each unused point, select the one that gives the most "left" or "right" turn
        for (int j = 0; j < n; ++j) {
            if (used[j] || j == nxt) continue;
            // If this is the last point, just pick any unused
            if (i == n - 2) continue;
            long long cr = cross(pts[cur], pts[nxt], pts[j]);
            if (s[i] == 'L') {
                // For left turn, pick the point with the largest cross product (most counterclockwise)
                if (cr < 0) nxt = j;
            } else {
                // For right turn, pick the point with the smallest cross product (most clockwise)
                if (cr > 0) nxt = j;
            }
        }
        order.push_back(nxt);
        used[nxt] = true;
    }

    // Output the permutation (1-based indices)
    for (int i = 0; i < n; ++i) {
        cout << pts[order[i]].idx << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}