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
    double norm() const { return sqrt(x * x + y * y); }
};

// Calculate the perimeter distances between points (precompute cumulative distances)
vector<double> precompute_distances(const vector<Point>& polygon) {
    vector<double> dists;
    dists.push_back(0);
    for (size_t i = 1; i < polygon.size(); ++i) {
        double d = (polygon[i] - polygon[i-1]).norm();
        dists.push_back(dists.back() + d);
    }
    return dists;
}

// Find the closest point on the polygon perimeter to the prisoner's starting point
double find_closest_point(const vector<Point>& polygon, const vector<double>& dists, const Point& prisoner) {
    double min_dist = 1e18;
    for (size_t i = 0; i < polygon.size() - 1; ++i) {
        Point a = polygon[i], b = polygon[i+1];
        Point ab = b - a;
        Point ap = prisoner - a;
        double t = ap.dot(ab) / ab.dot(ab);
        t = max(0.0, min(1.0, t));
        Point closest = a + Point(ab.x * t, ab.y * t);
        double dist = (closest - prisoner).norm();
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

// Binary search to find the minimal guard speed v
double solve(int n, const vector<Point>& polygon) {
    Point prisoner(-1e17, polygon.back().y / 2.0);
    vector<double> dists = precompute_distances(polygon);
    double total_perimeter = dists.back();
    
    // The prisoner's minimal time to reach the perimeter
    double prisoner_time = find_closest_point(polygon, dists, prisoner);
    
    // Binary search for minimal v
    double low = 0.0, high = 1e18;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (low + high) / 2;
        // The guards can cover a distance of mid * prisoner_time in total (both guards)
        // They need to cover the entire perimeter between them
        if (mid * prisoner_time >= total_perimeter / 2.0) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return low;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Point> polygon;
    for (int i = 0; i < n + 1; ++i) {
        double x, y;
        cin >> x >> y;
        polygon.emplace_back(x, y);
    }
    
    // The polygon is P1, P2, ..., P_{n+1}, and the other points are virtual
    // The perimeter is P1 -> P2 -> ... -> P_{n+1} -> P_{n+2} -> P_{n+3} -> P1
    // But P_{n+2} and P_{n+3} are at (-1e18, h) and (-1e18, 0), respectively
    // So the perimeter is the sum of the edges P1...P_{n+1} plus the edges to P_{n+2}, P_{n+3}, and back to P1
    // However, the prisoner can only escape via P1P2...P_{n+1}, so the guards must cover this part
    
    // The total perimeter the guards need to cover is the sum of P1P2 + P2P3 + ... + PnP_{n+1}
    double perimeter = 0;
    for (int i = 0; i < n; ++i) {
        perimeter += (polygon[i+1] - polygon[i]).norm();
    }
    
    // The prisoner's minimal time to reach any point on P1P2...P_{n+1}
    double min_prisoner_time = 1e18;
    for (int i = 0; i < n; ++i) {
        Point a = polygon[i], b = polygon[i+1];
        Point ab = b - a;
        Point ap = Point(-1e17, polygon.back().y / 2.0) - a;
        double t = ap.dot(ab) / ab.dot(ab);
        t = max(0.0, min(1.0, t));
        Point closest = a + Point(ab.x * t, ab.y * t);
        double dist = (closest - Point(-1e17, polygon.back().y / 2.0)).norm();
        if (dist < min_prisoner_time) {
            min_prisoner_time = dist;
        }
    }
    
    // The guards must cover the entire perimeter in time min_prisoner_time
    // Since there are two guards, they can cover up to 2 * v * min_prisoner_time distance
    // So 2 * v * min_prisoner_time >= perimeter => v >= perimeter / (2 * min_prisoner_time)
    double v = perimeter / (2.0 * min_prisoner_time);
    
    cout << fixed << setprecision(9) << v << endl;
    
    return 0;
}