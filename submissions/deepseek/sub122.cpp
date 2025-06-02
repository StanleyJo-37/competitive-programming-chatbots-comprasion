#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct Point {
    ll x, y;
    int idx;
};

// Cross product to determine the orientation (left or right turn)
ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].idx = i + 1;
    }
    string s;
    cin >> s;

    // Start with the leftmost point (or any extreme point to start the convex hull-like approach)
    int start = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].x < points[start].x || 
            (points[i].x == points[start].x && points[i].y < points[start].y)) {
            start = i;
        }
    }
    swap(points[0], points[start]);

    vector<int> perm;
    perm.push_back(points[0].idx);
    vector<bool> used(n, false);
    used[0] = true;

    for (int i = 0; i < n - 2; ++i) {
        int next = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                if (next == -1) {
                    next = j;
                } else {
                    ll c = cross(points[perm.back() - 1], points[next], points[j]);
                    if (s[i] == 'L') {
                        if (c < 0) {
                            next = j;
                        }
                    } else {
                        if (c > 0) {
                            next = j;
                        }
                    }
                }
            }
        }
        used[next] = true;
        perm.push_back(points[next].idx);
    }

    // Add the last remaining point
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            perm.push_back(points[i].idx);
            break;
        }
    }

    for (int num : perm) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}