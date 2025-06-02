#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Line {
    double a, b, c; // ax + by + c = 0
};

Line get_line(Point p1, Point p2) {
    Line l;
    l.a = p1.y - p2.y;
    l.b = p2.x - p1.x;
    l.c = -l.a * p1.x - l.b * p1.y;
    return l;
}

double dist_point_line(Point p, Line l) {
    return std::abs(l.a * p.x + l.b * p.y + l.c) / std::sqrt(l.a * l.a + l.b * l.b);
}

Point intersect_lines(Line l1, Line l2) {
    Point p;
    p.x = (l1.b * l2.c - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b);
    p.y = (l2.a * l1.c - l1.a * l2.c) / (l1.a * l2.b - l2.a * l1.b);
    return p;
}

double polygon_area(const std::vector<Point>& polygon) {
    double area = 0.0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        area += polygon[i].x * polygon[(i + 1) % n].y;
        area -= polygon[(i + 1) % n].x * polygon[i].y;
    }
    return std::abs(area) / 2.0;
}

Point centroid(const std::vector<Point>& polygon) {
    Point c = {0, 0};
    double area = polygon_area(polygon);
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        c.x += (polygon[i].x + polygon[(i + 1) % n].x) * (polygon[i].x * polygon[(i + 1) % n].y - polygon[(i + 1) % n].x * polygon[i].y);
        c.y += (polygon[i].y + polygon[(i + 1) % n].y) * (polygon[i].x * polygon[(i + 1) % n].y - polygon[(i + 1) % n].x * polygon[i].y);
    }
    c.x /= (6.0 * area);
    c.y /= (6.0 * area);
    return c;
}

bool is_inside(Point p, const std::vector<Point>& polygon) {
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];
        Line l = get_line(p1, p2);
        double val = l.a * p.x + l.b * p.y + l.c;
        if (val > EPS) { // Assuming counter-clockwise order, points inside should be on one side
            return false;
        }
    }
    return true;
}

double cross_product(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Check if point p is strictly inside the polygon
bool is_strictly_inside(Point p, const std::vector<Point>& polygon) {
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        if (std::abs(cross_product(polygon[i], polygon[(i + 1) % n], p)) < EPS) { // p is on edge
            double min_x = std::min(polygon[i].x, polygon[(i + 1) % n].x);
            double max_x = std::max(polygon[i].x, polygon[(i + 1) % n].x);
            double min_y = std::min(polygon[i].y, polygon[(i + 1) % n].y);
            double max_y = std::max(polygon[i].y, polygon[(i + 1) % n].y);
            if (p.x >= min_x - EPS && p.x <= max_x + EPS && p.y >= min_y - EPS && p.y <= max_y + EPS)
                return false; // Point is on an edge
        }
    }
    return is_inside(p, polygon);
}


// Function to check if a given r is feasible
bool check(double r, const std::vector<Point>& polygon, Point& res_p1, Point& res_p2) {
    int n = polygon.size();

    std::vector<Line> offset_lines[2]; // 0 for shrinking, 1 for growing
    std::vector<Line> lines_inside(n);

    for (int i = 0; i < n; ++i) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];
        Line l = get_line(p1, p2);
        double norm = std::sqrt(l.a * l.a + l.b * l.b);
        lines_inside[i] = {l.a, l.b, l.c + r * norm}; // For checking if points are inside
    }

    for (int i = 0; i < n; ++i) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];
        Line l = get_line(p1, p2);
        double norm = std::sqrt(l.a * l.a + l.b * l.b);

        offset_lines[0].push_back({l.a, l.b, l.c - r * norm}); // Shift inward
        offset_lines[1].push_back({l.a, l.b, l.c + r * norm}); // Shift outward (not used for feasibility check directly)
    }

    // Try all pairs of edges for intersection
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            Point p = intersect_lines(offset_lines[0][i], offset_lines[0][j]);

            bool p_inside_polygon = true;
            for (int k = 0; k < n; ++k) {
                Line current_line = get_line(polygon[k], polygon[(k + 1) % n]);
                if (current_line.a * p.x + current_line.b * p.y + current_line.c > EPS) {
                    p_inside_polygon = false;
                    break;
                }
            }

            if (p_inside_polygon) {
                // Check if this point covers all lines
                bool all_covered = true;
                for (int k = 0; k < n; ++k) {
                    if (dist_point_line(p, get_line(polygon[k], polygon[(k + 1) % n])) > r + EPS) {
                        all_covered = false;
                        break;
                    }
                }
                if (all_covered) {
                    res_p1 = p;
                    res_p2 = p;
                    return true;
                }
            }
        }
    }

    // Check edges and vertices
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Find two points P1 and P2 such that P1 covers line i, and P2 covers line j
            // and their combined coverage covers all lines
            // Consider the furthest points from lines i and j
            Point p1_candidate = centroid(polygon);
            Point p2_candidate = centroid(polygon);

            double max_dist_i = -1.0;
            double max_dist_j = -1.0;

            for(int k=0; k<n; ++k) {
                double d_i = dist_point_line(polygon[k], get_line(polygon[i], polygon[(i+1)%n]));
                double d_j = dist_point_line(polygon[k], get_line(polygon[j], polygon[(j+1)%n]));
                if (d_i > max_dist_i) {
                    max_dist_i = d_i;
                    p1_candidate = polygon[k];
                }
                if (d_j > max_dist_j) {
                    max_dist_j = d_j;
                    p2_candidate = polygon[k];
                }
            }

            // A more robust approach would be to find the points that are furthest from line i and j *within* the polygon
            // This is equivalent to finding the vertex of the polygon with maximum distance to the line.

            // Iterate over all pairs of polygon vertices for p1 and p2
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    Point current_p1 = polygon[k];
                    Point current_p2 = polygon[l];

                    if (!is_inside(current_p1, polygon) || !is_inside(current_p2, polygon)) continue; // Should not happen for polygon vertices

                    bool covered_by_p1 = true;
                    for(int m=0; m<n; ++m) {
                        if (dist_point_line(current_p1, get_line(polygon[m], polygon[(m+1)%n])) > r + EPS) {
                            covered_by_p1 = false;
                            break;
                        }
                    }

                    bool covered_by_p2 = true;
                    for(int m=0; m<n; ++m) {
                        if (dist_point_line(current_p2, get_line(polygon[m], polygon[(m+1)%n])) > r + EPS) {
                            covered_by_p2 = false;
                            break;
                        }
                    }

                    if (covered_by_p1 && covered_by_p2) {
                        res_p1 = current_p1;
                        res_p2 = current_p2;
                        return true;
                    }

                    bool combined_covered = true;
                    for (int m = 0; m < n; ++m) {
                        Line edge_line = get_line(polygon[m], polygon[(m + 1) % n]);
                        if (dist_point_line(current_p1, edge_line) > r + EPS && dist_point_line(current_p2, edge_line) > r + EPS) {
                            combined_covered = false;
                            break;
                        }
                    }
                    if (combined_covered) {
                        res_p1 = current_p1;
                        res_p2 = current_p2;
                        return true;
                    }
                }
            }
        }
    }

    // Two point solution:
    // For each pair of lines, find an optimal point for each, and check combined coverage.
    // This is getting complicated. The problem implies one point is sufficient if possible, or two points inside.
    // The previous loops try for one point solution and two points at vertices.

    // The key insight for two points is that for each edge, at least one circle must intersect.
    // This means for each edge, its distance from P1 <= r OR its distance from P2 <= r.
    // Let's re-evaluate the feasibility.
    // The set of points P for which dist(P, Line_i) <= r is a strip.
    // We need P1 and P2 such that for each i, P1 is in strip_i OR P2 is in strip_i.

    // A simpler approach for the check function for two points (P1, P2):
    // Find the minimum r such that for all lines Li, min(dist(P1, Li), dist(P2, Li)) <= r.
    // This is not what we are doing with binary search. We are finding the minimum r.

    // The property of the feasible region for a single point is an inner polygon.
    // For a single point, we just need to check if the shrunken polygon (from offset_lines[0]) is non-empty.
    // If it is, then any point in it works for a single point solution.
    // The intersection of half-planes defined by offset_lines[0] gives this shrunken polygon.
    // We can use an algorithm like half-plane intersection to find the resulting polygon.
    // If the resulting polygon is non-empty, then any point in it can be selected as P1 (and P2).

    // Let's implement half-plane intersection to find the feasible region for a single point.
    // A point `p` is valid if `dist(p, Line_i) <= r` for all `i`.
    // This means `|l.a * p.x + l.b * p.y + l.c| / norm <= r`.
    // Since polygon is convex and points are counter-clockwise, for interior points, `l.a * p.x + l.b * p.y + l.c` should be negative or zero.
    // So we need `l.a * p.x + l.b * p.y + l.c >= -r * norm`.
    // This is equivalent to `l.a * p.x + l.b * p.y + l.c + r * norm >= 0`.
    // This defines a shrunken polygon. If this shrunken polygon is non-empty, we can pick any point in it.

    // The half-plane intersection can be complex to implement correctly within a tight time limit.
    // A simpler way to check if a convex polygon (defined by a set of half-planes) is empty or not:
    // It is non-empty if the distances from a central point (e.g., centroid) to all half-planes are satisfied.
    // Or, if all pairs of intersecting lines result in a valid point. This is what the double loop tries.

    // Let's stick with the original approach of checking pairs of intersection points
    // of the offset lines for the single point solution.
    // If the intersection of offset_lines[0] is empty, then no single point works.

    // For two points, we use rotating calipers approach or iterate through pairs of vertices.
    // For a given r, we are looking for P1 and P2.
    // P1 covers a set of lines, P2 covers the rest.
    // We can iterate through all pairs of polygon vertices (P1, P2) and check if they work. This is O(N^2).
    // For each pair, check all N lines. So O(N^3) total per check. N=300, 300^3 = 2.7 * 10^7. Feasible.

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Point p1 = polygon[i];
            Point p2 = polygon[j];

            // Check if (p1, p2) is a valid pair for given r
            bool ok = true;
            for (int k = 0; k < n; ++k) {
                Line edge_line = get_line(polygon[k], polygon[(k + 1) % n]);
                if (dist_point_line(p1, edge_line) > r + EPS && dist_point_line(p2, edge_line) > r + EPS) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                res_p1 = p1;
                res_p2 = p2;
                return true;
            }
        }
    }

    return false;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<Point> polygon(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> polygon[i].x >> polygon[i].y;
    }

    // Binary search for r
    double low = 0.0, high = 20000.0; // Max possible distance for coords 10^4 is sqrt((2*10^4)^2 + (2*10^4)^2) ~ 2.8 * 10^4.
                                    // A safe upper bound for r would be half the maximum diagonal of the polygon, or even just max coordinate range.
    Point ans_p1, ans_p2;

    for (int iter = 0; iter < 100; ++iter) { // Fixed number of iterations for binary search precision
        double mid = (low + high) / 2.0;
        Point current_p1, current_p2;
        if (check(mid, polygon, current_p1, current_p2)) {
            high = mid;
            ans_p1 = current_p1;
            ans_p2 = current_p2;
        } else {
            low = mid;
        }
    }

    // After binary search, high holds the minimum r. ans_p1 and ans_p2 hold the corresponding points.
    // Re-run check with final high to ensure points are stored correctly, especially if the last successful check was for low.
    // It's possible that the last 'check' call passed with 'mid' (which became 'high'), but the stored points were from an earlier iteration
    // if 'mid' was on the 'low' side.
    // So, it's safer to call check once more with the final 'high' value.
    Point final_p1, final_p2;
    check(high, polygon, final_p1, final_p2); // This call finds *any* valid pair for 'high'.

    std::cout << std::fixed << std::setprecision(7) << high << std::endl;
    std::cout << std::fixed << std::setprecision(7) << final_p1.x << " " << final_p1.y << std::endl;
    std::cout << std::fixed << std::setprecision(7) << final_p2.x << " " << final_p2.y << std::endl;

    return 0;
}