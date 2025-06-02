#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector
#include <string>   // Required for std::string
#include <algorithm> // Required for std::min (though not explicitly used, good practice for competitive programming)

// Structure to represent a point with its coordinates and original 1-based ID.
struct Point {
    long long x, y; // Coordinates can be large, so use long long.
    int id;         // Original 1-based ID of the point.
};

// Function to calculate the 2D cross product of vectors AB and BC.
// This determines the orientation of point C relative to the directed line segment AB.
// A positive value means C is to the left (counter-clockwise) of AB.
// A negative value means C is to the right (clockwise) of AB.
// A zero value means A, B, C are collinear (guaranteed not to happen for any three points by problem statement).
long long cross_product(Point A, Point B, Point C) {
    // Vector AB: (B.x - A.x, B.y - A.y)
    // Vector BC: (C.x - B.x, C.y - B.y)
    // Cross product formula: (x1*y2 - y1*x2) where v1=(x1,y1), v2=(x2,y2)
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}

// Function to calculate the squared Euclidean distance between two points.
// Used for tie-breaking when comparing polar angles of collinear points.
long long distSq(Point A, Point B) {
    long long dx = A.x - B.x;
    long long dy = A.y - B.y;
    return dx * dx + dy * dy;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of points.
    std::cin >> n;

    std::vector<Point> points(n); // Vector to store all points.
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
        points[i].id = i + 1; // Store 1-based original ID.
    }

    std::string s; // String of 'L' and 'R' characters for turn directions.
    std::cin >> s;

    // p will store the indices (into the 'points' vector) of the points in the final permutation.
    std::vector<int> p(n);
    // used tracks which points have already been added to the permutation.
    std::vector<bool> used(n, false);

    // Step 1: Find the first point (p[0]).
    // Choose the point with the minimum y-coordinate. If ties, choose the one with minimum x-coordinate.
    // This point is guaranteed to be on the convex hull and provides a consistent starting point.
    int first_idx = 0; // Initialize with the first point.
    for (int i = 1; i < n; ++i) {
        if (points[i].y < points[first_idx].y || (points[i].y == points[first_idx].y && points[i].x < points[first_idx].x)) {
            first_idx = i; // Update if a point with smaller y (or same y and smaller x) is found.
        }
    }
    p[0] = first_idx;     // Assign the chosen point's index to the first position in the permutation.
    used[first_idx] = true; // Mark the point as used.

    // Step 2: Find the second point (p[1]).
    // Among the remaining (unused) points, choose the one that forms the smallest polar angle
    // with p[0] and the positive x-axis. This is a standard step in convex hull algorithms.
    // It's equivalent to finding P_k such that all other unused points P_j are to the right
    // of the vector P_0 -> P_k (i.e., cross_product(P_0, P_k, P_j) < 0 for all P_j).
    int second_idx = -1; // Initialize candidate for p[1].
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue; // Skip already used points.

        if (second_idx == -1) {
            second_idx = i; // Initialize with the first unused point found.
        } else {
            // Calculate cross product for points[first_idx] -> points[second_idx] -> points[i].
            long long cp = cross_product(points[first_idx], points[second_idx], points[i]);
            if (cp > 0) {
                // points[i] is to the left of points[first_idx]->points[second_idx].
                // This means points[i] forms a smaller polar angle relative to points[first_idx].
                // So, points[i] is a better candidate for second_idx.
                second_idx = i;
            } else if (cp == 0) {
                // Points are collinear. Choose the one further away from points[first_idx].
                // This ensures that all points on the "edge" are included in the path.
                long long dist_second = distSq(points[first_idx], points[second_idx]);
                long long dist_i = distSq(points[first_idx], points[i]);
                if (dist_i > dist_second) {
                    second_idx = i;
                }
            }
            // If cp < 0, points[i] is to the right, meaning points[second_idx] has a smaller angle. Do nothing.
        }
    }
    p[1] = second_idx;     // Assign the chosen point's index to the second position.
    used[second_idx] = true; // Mark the point as used.

    // Step 3: Find the remaining points (p[2] to p[n-1]).
    // For each step k from 2 up to n-1, we need to find p[k].
    // The turn at A_{p_{k-1}} (from A_{p_{k-2}} -> A_{p_{k-1}} to A_{p_{k-1}} -> A_{p_k})
    // must match the direction specified by s[k-2].
    // We choose the point that makes the "sharpest" turn in the required direction.
    for (int k = 2; k < n; ++k) {
        int prev_point_idx = p[k-2]; // Index of the point A_{p_{k-1}} in 'points' array.
        int curr_point_idx = p[k-1]; // Index of the point A_{p_k} in 'points' array.

        int next_point_idx = -1; // Candidate for the next point A_{p_{k+1}}.
        // Initialize best_cross_val to an extreme value.
        // Max possible cross product is approx 4 * 10^18. Using 5e18 as a safe bound.
        long long best_cross_val = (s[k-2] == 'L' ? -5e18 : 5e18); 

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue; // Skip already used points.

            // Calculate cross product for the potential turn: A_{p_{k-1}} -> A_{p_k} -> A_i.
            long long current_cross_val = cross_product(points[prev_point_idx], points[curr_point_idx], points[i]);

            if (s[k-2] == 'L') { // Required turn is Left (cross product > 0).
                if (current_cross_val > 0) { // Check if it's a valid left turn.
                    if (next_point_idx == -1 || current_cross_val > best_cross_val) {
                        // If this is the first valid point, or it makes a sharper left turn (larger positive cross product).
                        best_cross_val = current_cross_val;
                        next_point_idx = i;
                    }
                }
            } else { // Required turn is Right (cross product < 0).
                if (current_cross_val < 0) { // Check if it's a valid right turn.
                    if (next_point_idx == -1 || current_cross_val < best_cross_val) {
                        // If this is the first valid point, or it makes a sharper right turn (smaller negative cross product).
                        best_cross_val = current_cross_val;
                        next_point_idx = i;
                    }
                }
            }
        }

        // If after checking all unused points, no valid point was found,
        // it means no solution exists with this greedy strategy.
        // This implies that all remaining points would result in a turn opposite to the required one.
        if (next_point_idx == -1) {
            std::cout << -1 << std::endl; // Print -1 and exit.
            return 0;
        }

        p[k] = next_point_idx;     // Assign the chosen point's index to the current position.
        used[next_point_idx] = true; // Mark the point as used.
    }

    // Output the original 1-based IDs of the points in the found permutation.
    for (int i = 0; i < n; ++i) {
        std::cout << points[p[i]].id << (i == n - 1 ? "" : " "); // Print space between numbers, no space after last.
    }
    std::cout << std::endl; // Newline at the end.

    return 0; // Indicate successful execution.
}
