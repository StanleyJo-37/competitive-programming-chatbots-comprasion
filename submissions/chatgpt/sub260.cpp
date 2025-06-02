#include <bits/stdc++.h>
using namespace std;

// Constants
const double EPS = 1e-8;
const double INF = 1e18;

// Point structure for 2D geometry
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }
    double dot(const Point &b) const { return x * b.x + y * b.y; }
    double cross(const Point &b) const { return x * b.y - y * b.x; }
    double norm2() const { return x * x + y * y; }
    double norm() const { return sqrt(norm2()); }
};

// Distance from point p to line (a, b)
double distToLine(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    return fabs(ab.cross(ap)) / ab.norm();
}

// Check if point p is inside convex polygon poly (including on edge)
bool pointInConvexPolygon(const vector<Point> &poly, Point p) {
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i+1)%n];
        if ((b - a).cross(p - a) < -EPS) return false;
    }
    return true;
}

// For a given r, check if there exist two points inside polygon such that
// for every edge line, at least one of the two circles of radius r centered at those points
// touches the edge line.
bool check(double r, const vector<Point> &poly, Point &res1, Point &res2) {
    int n = poly.size();
    vector<pair<Point, Point>> lines; // Each edge as (a, b)
    for (int i = 0; i < n; ++i) {
        lines.push_back({poly[i], poly[(i+1)%n]});
    }

    // For each edge, we want to find a point inside the polygon whose distance to the edge's line is <= r
    // For each edge, the set of such points is the strip of width 2r around the edge's line, intersected with the polygon

    // For each edge, we can pick a point inside the polygon at distance <= r from the edge's line
    // If we can cover all edges with one point, then r is enough (r=0 is possible if two vertices)
    // Otherwise, we need to cover the edges with two such points

    // For each edge, we can sample a point inside the polygon at distance <= r from the edge's line
    // Let's try to greedily cover as many edges as possible with one point, then the rest with another

    // For each edge, sample a point inside the polygon at distance <= r from the edge's line
    // For each edge, we can take the closest point in the polygon to the edge's line

    // For each edge, find the set of points inside the polygon at distance <= r from the edge's line
    // For each edge, sample a point inside the polygon at distance exactly r from the edge's line (on the normal direction)
    // For each edge, sample the midpoint of the edge, move r towards the inside

    // For each edge, we can compute the normal vector pointing inside the polygon
    vector<Point> normals(n);
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i+1)%n];
        Point edge = b - a;
        // Outward normal is (edge.y, -edge.x), inward is (-edge.y, edge.x)
        Point normal = Point(-(edge.y), edge.x);
        double len = sqrt(normal.x * normal.x + normal.y * normal.y);
        normal = normal / len;
        // Check if normal points inside: take a point inside (centroid), see if it is on the correct side
        Point mid = (a + b) * 0.5;
        Point centroid(0, 0);
        for (auto &p : poly) centroid = centroid + p;
        centroid = centroid / n;
        Point test = mid + normal * 1.0;
        double cross = (b - a).cross(centroid - a);
        double cross2 = (b - a).cross(test - a);
        if (cross * cross2 < 0) normal = normal * -1; // flip if not pointing inside
        normals[i] = normal;
    }

    // For each edge, sample a point inside the polygon at distance r from the edge's line
    vector<Point> candidates;
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i+1)%n];
        Point mid = (a + b) * 0.5;
        Point p = mid + normals[i] * r;
        if (pointInConvexPolygon(poly, p)) {
            candidates.push_back(p);
        }
        // Also try at 1/3 and 2/3 along the edge
        Point p1 = a * (2.0/3.0) + b * (1.0/3.0) + normals[i] * r;
        Point p2 = a * (1.0/3.0) + b * (2.0/3.0) + normals[i] * r;
        if (pointInConvexPolygon(poly, p1)) candidates.push_back(p1);
        if (pointInConvexPolygon(poly, p2)) candidates.push_back(p2);
    }
    // Also add all vertices as candidates
    for (int i = 0; i < n; ++i) {
        if (pointInConvexPolygon(poly, poly[i])) candidates.push_back(poly[i]);
    }
    // Also add centroid
    Point centroid(0, 0);
    for (auto &p : poly) centroid = centroid + p;
    centroid = centroid / n;
    if (pointInConvexPolygon(poly, centroid)) candidates.push_back(centroid);

    // For each candidate, compute which edges' lines are within r
    int m = candidates.size();
    vector<vector<int>> covers(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            Point a = poly[j], b = poly[(j+1)%n];
            double d = distToLine(candidates[i], a, b);
            if (d <= r + EPS) covers[i].push_back(j);
        }
    }

    // Try to cover all edges with one candidate
    for (int i = 0; i < m; ++i) {
        if ((int)covers[i].size() == n) {
            res1 = candidates[i];
            res2 = candidates[i];
            return true;
        }
    }

    // Try to cover all edges with two candidates
    // For each pair, check if their union covers all edges
    for (int i = 0; i < m; ++i) {
        vector<bool> vis(n, false);
        for (int e : covers[i]) vis[e] = true;
        for (int j = i; j < m; ++j) {
            vector<bool> vis2 = vis;
            for (int e : covers[j]) vis2[e] = true;
            bool ok = true;
            for (int k = 0; k < n; ++k) if (!vis2[k]) ok = false;
            if (ok) {
                res1 = candidates[i];
                res2 = candidates[j];
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Point> poly(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        poly[i] = Point(x, y);
    }

    // Binary search for minimal r
    double l = 0, r = 2e4; // upper bound is enough for all cases
    Point ans1, ans2;
    for (int iter = 0; iter < 60; ++iter) { // enough for 1e-7 precision
        double mid = (l + r) / 2;
        Point p1, p2;
        if (check(mid, poly, p1, p2)) {
            r = mid;
            ans1 = p1;
            ans2 = p2;
        } else {
            l = mid;
        }
    }

    // Output
    cout << fixed << setprecision(10) << r << '\n';
    cout << fixed << setprecision(10) << ans1.x << ' ' << ans1.y << '\n';
    cout << fixed << setprecision(10) << ans2.x << ' '