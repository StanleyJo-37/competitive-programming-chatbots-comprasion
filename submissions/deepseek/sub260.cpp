#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-8
#define INF 1e18

typedef double T;

struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(T d) const { return Point(x * d, y * d); }
    Point operator/(T d) const { return Point(x / d, y / d); }
    T dot(const Point &p) const { return x * p.x + y * p.y; }
    T cross(const Point &p) const { return x * p.y - y * p.x; }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }
    Point rotate(double a) const { return Point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)); }
    bool operator==(const Point &p) const { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
    bool operator<(const Point &p) const { return x < p.x || (x == p.x && y < p.y); }
};

struct Line {
    Point a, b;
    Line() {}
    Line(Point a, Point b) : a(a), b(b) {}
};

// Check if point p is inside or on the boundary of the convex polygon
bool pointInConvexPolygon(const vector<Point> &poly, const Point &p) {
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i+1)%n];
        if ((b - a).cross(p - a) < -EPS) return false;
    }
    return true;
}

// Compute the distance from point p to line l
double pointLineDistance(const Point &p, const Line &l) {
    Point ab = l.b - l.a, ap = p - l.a;
    double t = ap.dot(ab) / ab.dist2();
    if (t < 0.0) return (p - l.a).dist();
    if (t > 1.0) return (p - l.b).dist();
    return sqrt(ap.dist2() - t * t * ab.dist2());
}

// Compute the intersection of two lines
Point lineIntersection(const Line &l1, const Line &l2) {
    Point a = l1.a, b = l1.b, c = l2.a, d = l2.b;
    T a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1*a.x + b1*a.y;
    T a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2*c.x + b2*c.y;
    T det = a1*b2 - a2*b1;
    if (fabs(det) < EPS) return Point(INF, INF); // parallel or coincident
    return Point((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det);
}

// Binary search to find the minimal r such that two circles of radius r cover all edge lines
pair<Point, Point> findMinimalRCenters(const vector<Point> &poly, double r) {
    int n = poly.size();
    vector<Line> edges;
    for (int i = 0; i < n; i++) {
        edges.emplace_back(poly[i], poly[(i+1)%n]);
    }

    // Function to check if two circles of radius r cover all edge lines
    auto isPossible = [&](double r) {
        vector<Point> candidates;
        // Generate candidate points (offset from edges by r)
        for (int i = 0; i < n; i++) {
            Line edge = edges[i];
            Point dir = (edge.b - edge.a);
            Point perp = Point(-dir.y, dir.x);
            perp = perp / perp.dist();
            Point offset = perp * r;
            Point p1 = edge.a + offset;
            Point p2 = edge.a - offset;
            Point p3 = edge.b + offset;
            Point p4 = edge.b - offset;
            candidates.push_back(p1);
            candidates.push_back(p2);
            candidates.push_back(p3);
            candidates.push_back(p4);
        }

        // Also consider polygon vertices as potential centers
        for (const Point &p : poly) {
            candidates.push_back(p);
        }

        // Check all pairs of candidate points
        for (int i = 0; i < candidates.size(); i++) {
            Point c1 = candidates[i];
            if (!pointInConvexPolygon(poly, c1)) continue;
            for (int j = i; j < candidates.size(); j++) {
                Point c2 = candidates[j];
                if (!pointInConvexPolygon(poly, c2)) continue;
                bool allCovered = true;
                for (const Line &edge : edges) {
                    double d1 = pointLineDistance(c1, edge);
                    double d2 = pointLineDistance(c2, edge);
                    if (d1 > r + EPS && d2 > r + EPS) {
                        allCovered = false;
                        break;
                    }
                }
                if (allCovered) {
                    return make_pair(c1, c2);
                }
            }
        }
        return make_pair(Point(INF, INF), Point(INF, INF));
    };

    pair<Point, Point> res = isPossible(r);
    if (res.first.x != INF) return res;
    return make_pair(Point(INF, INF), Point(INF, INF));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> poly(n);
    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }

    double low = 0.0, high = 1e5;
    Point bestA, bestB;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (low + high) / 2;
        auto centers = findMinimalRCenters(poly, mid);
        if (centers.first.x != INF) {
            high = mid;
            bestA = centers.first;
            bestB = centers.second;
        } else {
            low = mid;
        }
    }

    cout << fixed << setprecision(7) << high << '\n';
    cout << bestA.x << ' ' << bestA.y << '\n';
    cout << bestB.x << ' ' << bestB.y << '\n';

    return 0;
}