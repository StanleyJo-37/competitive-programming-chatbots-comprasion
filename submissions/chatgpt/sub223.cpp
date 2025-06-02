#include <bits/stdc++.h>
using namespace std;

// Point structure for 2D geometry
struct Point {
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    Point operator-(const Point& b) const { return Point(x-b.x, y-b.y); }
    Point operator+(const Point& b) const { return Point(x+b.x, y+b.y); }
    Point operator*(double t) const { return Point(x*t, y*t); }
    double dot(const Point& b) const { return x*b.x + y*b.y; }
    double cross(const Point& b) const { return x*b.y - y*b.x; }
    double norm() const { return sqrt(x*x + y*y); }
};

// Function to compute the distance from a point to a segment
double distToSegment(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    double t = ab.dot(ap) / ab.dot(ab);
    t = max(0.0, min(1.0, t));
    Point proj = a + ab * t;
    return (p - proj).norm();
}

// Function to compute the closest point on segment ab to point p
Point closestPoint(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    double t = ab.dot(ap) / ab.dot(ab);
    t = max(0.0, min(1.0, t));
    return a + ab * t;
}

// Function to compute the length of a polyline
double polylineLength(const vector<Point>& poly) {
    double len = 0;
    for (int i = 1; i < (int)poly.size(); ++i)
        len += (poly[i] - poly[i-1]).norm();
    return len;
}

// Function to compute the distance along the perimeter from P1 to a point on the escape wall
double perimeterDist(const vector<Point>& poly, vector<double>& accLen, int seg, double t) {
    // accLen[i] = length from P1 to poly[i]
    double segLen = (poly[seg+1] - poly[seg]).norm();
    return accLen[seg] + segLen * t;
}

// Main function
int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Point> poly(n+1);
    for (int i = 0; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        poly[i] = Point(x, y);
    }
    // h is y-coordinate of P_{n+1}
    double h = poly[n].y;

    // The escape wall is the polyline from P1 to P_{n+1}
    // The perimeter is the polyline from P1 to P_{n+1}, then up to (-1e18, h), then to (-1e18, 0), then to (0,0)
    // But the only escape is on the first n segments: P1P2, P2P3, ..., PnP_{n+1}

    // Precompute the cumulative length along the perimeter for the escape wall
    vector<double> accLen(n+2, 0.0); // accLen[i] = length from P1 to poly[i]
    for (int i = 1; i <= n; ++i)
        accLen[i] = accLen[i-1] + (poly[i] - poly[i-1]).norm();
    double escapeWallLen = accLen[n];

    // The total perimeter is escapeWallLen + the three vertical/left walls
    // But guards can only move on the perimeter

    // Prisoner's initial position
    Point prisoner(-1e17, h/2);

    // For a given v, check if guards can always intercept the prisoner
    auto can_catch = [&](double v) -> bool {
        // For every point on the escape wall, compute:
        // - time for prisoner to reach it: Euclidean distance from prisoner to that point
        // - time for the closest guard to reach it: minimal of (distance along perimeter from P1 to that point) / v and (distance along perimeter from P_{n+1} to that point) / v
        // Guards start at P1, but two guards can split and cover both ends, so the minimal time is the minimal of the two
        // If for every point, the guard can reach it not later than the prisoner, then guards can always catch

        // We discretize the escape wall finely enough
        int samples = 1000;
        for (int seg = 0; seg < n; ++seg) {
            Point a = poly[seg], b = poly[seg+1];
            for (int s = 0; s <= samples; ++s) {
                double t = (double)s / samples;
                Point q = a + (b - a) * t;
                double prisoner_time = (q - prisoner).norm();
                double guard_time1 = (accLen[seg] + ((b - a).norm()) * t) / v; // from P1
                double guard_time2 = (escapeWallLen - (accLen[seg] + ((b - a).norm()) * t)) / v; // from P_{n+1}
                double guard_time = min(guard_time1, guard_time2);
                if (prisoner_time < guard_time - 1e-8) // guard cannot reach before prisoner
                    return false;
            }
        }
        return true;
    };

    // Binary search for minimal v
    double lo = 0.0, hi = 1e5;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (lo + hi) / 2;
        if (can_catch(mid))
            hi = mid;
        else
            lo = mid;
    }
    cout << fixed << setprecision(10) << hi << '\n';
    return 0;
}