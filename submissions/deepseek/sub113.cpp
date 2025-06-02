#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to calculate the Manhattan distance between two points (x1, y1) and (x2, y2)
ll manhattan(ll x1, ll y1, ll x2, ll y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    ll x0, y0, ax, ay, bx, by;
    cin >> x0 >> y0 >> ax >> ay >> bx >> by;
    ll xs, ys, t;
    cin >> xs >> ys >> t;

    vector<pair<ll, ll>> nodes;
    nodes.emplace_back(x0, y0);

    // Generate nodes until their coordinates exceed a reasonable bound (since t is up to 1e16)
    while (true) {
        ll last_x = nodes.back().first;
        ll last_y = nodes.back().second;
        ll new_x = ax * last_x + bx;
        ll new_y = ay * last_y + by;
        // Stop if the new node is too far away to be reachable within t seconds from (xs, ys)
        if (new_x > xs + t || new_y > ys + t) break;
        nodes.emplace_back(new_x, new_y);
    }

    int max_nodes = 0;
    int n = nodes.size();

    // Check all possible sequences of nodes (i to j) to find the maximum collectible nodes within t seconds
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            // Calculate the minimal time to collect nodes from i to j
            ll total_time = 0;
            // Option 1: Start at i, move to j (i -> i+1 -> ... -> j)
            ll time1 = manhattan(xs, ys, nodes[i].first, nodes[i].second);
            for (int k = i; k < j; ++k) {
                time1 += manhattan(nodes[k].first, nodes[k].second, nodes[k+1].first, nodes[k+1].second);
            }
            // Option 2: Start at j, move to i (j -> j-1 -> ... -> i)
            ll time2 = manhattan(xs, ys, nodes[j].first, nodes[j].second);
            for (int k = j; k > i; --k) {
                time2 += manhattan(nodes[k].first, nodes[k].second, nodes[k-1].first, nodes[k-1].second);
            }
            // Take the minimal time between the two options
            ll min_time = min(time1, time2);
            if (min_time <= t) {
                max_nodes = max(max_nodes, j - i + 1);
            }
        }
    }

    cout << max_nodes << endl;
    return 0;
}