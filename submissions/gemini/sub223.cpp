#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

// Define a Point structure for convenience
struct Point {
    double x, y;
};

// Function to calculate Euclidean distance between two points
double dist(Point p1, Point p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Store the vertices P_1, ..., P_{n+1}
    // Using 0-indexed vector, so P[0] is P_1, P[n] is P_{n+1}
    std::vector<Point> P(n + 1);
    for (int i = 0; i <= n; ++i) {
        std::cin >> P[i].x >> P[i].y;
    }

    // Prisoner's starting position S
    // P_1 is (0,0), P_{n+1} is (0, h) where h = P[n].y
    double h = P[n].y;
    Point S = {-1e17, h / 2.0};

    // Precompute prefix sums of distances along the climbable perimeter P_1P_2...P_{n+1}
    // lenA[i] will store the distance from P_1 to P_{i+1} along the perimeter
    // lenA[0] = distance from P_1 to P_1 (0)
    // lenA[1] = distance from P_1 to P_2
    // ...
    // lenA[n] = distance from P_1 to P_{n+1}
    std::vector<double> lenA(n + 1);
    lenA[0] = 0.0;
    for (int i = 0; i < n; ++i) {
        lenA[i + 1] = lenA[i] + dist(P[i], P[i + 1]);
    }

    // The total length of the climbable perimeter (P_1 to P_{n+1})
    // double L_total_climbable = lenA[n]; // Not directly used after simplification

    // The full perimeter of the prison includes the "very high" walls:
    // P_1 -> P_2 -> ... -> P_{n+1} (length L_total_climbable)
    // P_{n+1} -> P_{n+2} (length 10^18)
    // P_{n+2} -> P_{n+3} (length h)
    // P_{n+3} -> P_1 (length 10^18)
    // The total length of the full perimeter is L_total_climbable + 2.0 * 1e18 + h.
    // As explained in the thought process, the "back path" (via P_{n+2}, P_{n+3}) is
    // extremely long compared to the "front path" (Path_A).
    // Thus, for any point T on Path_A, the distance along Path_A (d_cw(T)) will always be
    // much smaller than half the full perimeter.
    // This means min(d_cw(T), L_full_perimeter - d_cw(T)) simplifies to d_cw(T).
    // So, the problem effectively reduces to a single guard problem where the guard only uses the climbable path.

    double max_v = 0.0;

    // Iterate through each segment P_i P_{i+1} of the climbable perimeter
    for (int i = 0; i < n; ++i) {
        // Define a lambda function to calculate v for a point T on segment P[i]P[i+1]
        // T is parameterized by alpha: T = P[i] + alpha * (P[i+1] - P[i])
        // alpha ranges from 0 to 1
        auto calculate_v = [&](double alpha) {
            // Calculate coordinates of T
            Point current_P = {
                P[i].x + alpha * (P[i+1].x - P[i].x),
                P[i].y + alpha * (P[i+1].y - P[i].y)
            };

            // Distance for guard to reach T along the climbable path
            // This is lenA[i] (distance to P[i]) + alpha * dist(P[i], P[i+1]) (distance from P[i] to T)
            double guard_dist = lenA[i] + alpha * dist(P[i], P[i+1]);

            // Distance for prisoner to reach T (straight line)
            double prisoner_dist = dist(S, current_P);

            // prisoner_dist will always be positive because S is far from the climbable perimeter.
            return guard_dist / prisoner_dist;
        };

        // Use ternary search to find the maximum v on the current segment [0, 1] for alpha
        double left = 0.0, right = 1.0;
        // 100 iterations are sufficient for double precision (error ~ (1/3)^100)
        for (int iter = 0; iter < 100; ++iter) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;
            if (calculate_v(m1) < calculate_v(m2)) {
                left = m1;
            } else {
                right = m2;
            }
        }
        // The maximum value is at 'left' (or 'right', or their average) after ternary search
        max_v = std::max(max_v, calculate_v(left));
    }

    // Print the result with required precision
    std::cout << std::fixed << std::setprecision(9) << max_v << std::endl;

    return 0;
}
