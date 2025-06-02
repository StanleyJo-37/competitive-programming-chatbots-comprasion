#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Function to compute Manhattan distance between two points
long long manhattan(long long x1, long long y1, long long x2, long long y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    // Read input for node generation
    long long x0, y0, ax, ay, bx, by;
    cin >> x0 >> y0 >> ax >> ay >> bx >> by;

    // Read input for Aroma's start and time
    long long xs, ys, t;
    cin >> xs >> ys >> t;

    // Generate all nodes that could possibly be reached within time t
    // Since coordinates grow exponentially, we only need to generate nodes
    // that are within a reasonable distance from (xs, ys)
    vector<pair<long long, long long>> nodes;
    long long x = x0, y = y0;
    while (true) {
        // If the node is so far that even from the start point it's impossible to reach within t, break
        if (manhattan(xs, ys, x, y) > t && !nodes.empty()) {
            // But we still need to check further nodes for possible better routes, so don't break yet
            // Instead, break if the coordinates are too large to avoid overflow
            if (x > 2e16 || y > 2e16) break;
        }
        nodes.push_back({x, y});
        // Prepare next node, but check for overflow
        if (x > (LLONG_MAX - bx) / ax || y > (LLONG_MAX - by) / ay) break;
        x = ax * x + bx;
        y = ay * y + by;
    }

    int n = nodes.size();
    int ans = 0;

    // Try all possible intervals [i, j] (i <= j), and both directions
    // For each interval, try starting from i or j, and see if it's possible to collect all nodes in [i, j]
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            // Try starting from i and going to j
            long long cost1 = manhattan(xs, ys, nodes[i].first, nodes[i].second); // go to i
            cost1 += manhattan(nodes[i].first, nodes[i].second, nodes[j].first, nodes[j].second); // traverse to j
            // Try starting from j and going to i
            long long cost2 = manhattan(xs, ys, nodes[j].first, nodes[j].second); // go to j
            cost2 += manhattan(nodes[j].first, nodes[j].second, nodes[i].first, nodes[i].second); // traverse to i
            // If either direction is possible within t, update answer
            if (cost1 <= t || cost2 <= t) {
                ans = max(ans, j - i + 1);
            }
        }
    }

    cout << ans << endl;
    return 0;
}