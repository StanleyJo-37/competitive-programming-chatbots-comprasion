#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// Structure to represent a point in 2D
struct Point {
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    // Subtract two points
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    // Compute squared distance to another point
    double dist2(const Point& other) const {
        double dx = x - other.x, dy = y - other.y;
        return dx*dx + dy*dy;
    }
    // Compute distance to another point
    double dist(const Point& other) const {
        return sqrt(dist2(other));
    }
};

// Compute the squared distance from point p to segment ab
double dist2_point_to_segment(const Point& p, const Point& a, const Point& b) {
    // Vector from a to b
    double dx = b.x - a.x, dy = b.y - a.y;
    // If a == b, return distance to a
    if (dx == 0 && dy == 0) return p.dist2(a);
    // Project point p onto the line ab, computing parameter t
    double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (dx*dx + dy*dy);
    // Clamp t to [0,1] to stay within the segment
    t = max(0.0, min(1.0, t));
    // Compute the closest point on the segment
    double proj_x = a.x + t * dx;
    double proj_y = a.y + t * dy;
    // Return squared distance from p to the closest point
    double ddx = p.x - proj_x, ddy = p.y - proj_y;
    return ddx*ddx + ddy*ddy;
}

int main() {
    int n;
    double px, py;
    cin >> n >> px >> py;
    vector<Point> poly(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        poly[i] = Point(x, y);
    }
    Point P(px, py);

    // Find the maximum and minimum squared distances from P to the polygon
    double max_r2 = 0.0, min_r2 = 1e20;
    // For each vertex, update max and min squared distance
    for (int i = 0; i < n; ++i) {
        double d2 = P.dist2(poly[i]);
        max_r2 = max(max_r2, d2);
        min_r2 = min(min_r2, d2);
    }
    // For each edge, update min squared distance (for the closest point on the edge)
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n;
        double d2 = dist2_point_to_segment(P, poly[i], poly[j]);
        min_r2 = min(min_r2, d2);
    }

    // The area cleared is the area of the annulus: pi * (R^2 - r^2)
    const double PI = acos(-1.0);
    double area = PI * (max_r2 - min_r2);

    // Output with sufficient precision
    cout << fixed << setprecision(15) << area << endl;
    return 0;
}