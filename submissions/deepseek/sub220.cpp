#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }
};

// Compute the area of the swept region by the polygon around point P.
int main() {
    int n;
    Point P;
    cin >> n >> P.x >> P.y;
    vector<Point> polygon(n);
    for (int i = 0; i < n; ++i) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    double min_r2 = 1e18, max_r2 = 0;

    // Iterate over all vertices to find min and max distances squared.
    for (const Point& vertex : polygon) {
        Point diff = vertex - P;
        double r2 = diff.dist2();
        min_r2 = min(min_r2, r2);
        max_r2 = max(max_r2, r2);
    }

    // Iterate over edges to check if the minimal distance is from a point to a segment.
    for (int i = 0; i < n; ++i) {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % n];
        Point ab = b - a;
        Point ap = P - a;
        double t = ap.dot(ab) / ab.dist2();
        if (t >= 0 && t <= 1) {
            Point projection = a + Point(ab.x * t, ab.y * t);
            Point diff = projection - P;
            double r2 = diff.dist2();
            min_r2 = min(min_r2, r2);
        }
    }

    double area = M_PI * (max_r2 - min_r2);
    cout << fixed << setprecision(15) << area << endl;

    return 0;
}