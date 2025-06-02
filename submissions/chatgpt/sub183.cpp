#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree (Binary Indexed Tree) for range sum queries and point updates
struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int n) : n(n), bit(n+2, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    int range(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

struct Road {
    int x1, y1, x2, y2;
    bool is_horizontal;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<Road> roads(N);
    vector<tuple<int,int,int,int>> horizontals; // (y, x1, x2, idx)
    vector<tuple<int,int,int,int>> verticals;   // (x, y1, y2, idx)
    vector<int> ans(N, 0);

    // Read input and classify roads
    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2 || y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if (y1 == y2) {
            // horizontal
            horizontals.emplace_back(y1, x1, x2, i);
            roads[i] = {x1, y1, x2, y2, true, i};
        } else {
            // vertical
            verticals.emplace_back(x1, y1, y2, i);
            roads[i] = {x1, y1, x2, y2, false, i};
        }
    }

    // Coordinate compression for x and y
    set<int> x_set, y_set;
    for (auto &[y, x1, x2, idx] : horizontals) {
        x_set.insert(x1);
        x_set.insert(x2);
        y_set.insert(y);
    }
    for (auto &[x, y1, y2, idx] : verticals) {
        x_set.insert(x);
        y_set.insert(y1);
        y_set.insert(y2);
    }
    // Map original coordinates to compressed ones
    map<int, int> x_map, y_map;
    int x_cnt = 1, y_cnt = 1;
    for (int x : x_set) x_map[x] = x_cnt++;
    for (int y : y_set) y_map[y] = y_cnt++;

    // Prepare events for sweep line
    // Each event: (y, type, x1, x2, idx)
    // type: 0 = add horizontal, 1 = query vertical, 2 = remove horizontal
    vector<tuple<int,int,int,int,int>> events;
    for (auto &[y, x1, x2, idx] : horizontals) {
        events.emplace_back(y_map[y], 0, x_map[x1], x_map[x2], idx); // add
        events.emplace_back(y_map[y], 2, x_map[x1], x_map[x2], idx); // remove (same y, but will be processed after query)
    }
    for (auto &[x, y1, y2, idx] : verticals) {
        events.emplace_back(y_map[y1], 1, x_map[x], y_map[y2], idx); // query at y1
    }
    // Sort events: by y, then type (add < query < remove)
    sort(events.begin(), events.end());

    // Fenwick Tree for active horizontals
    FenwickTree ft(x_cnt+2);

    // For each vertical, store intersections
    vector<vector<pair<int,int>>> vertical_intersections(N); // idx -> list of (y, x)
    vector<vector<pair<int,int>>> horizontal_intersections(N); // idx -> list of (x, y)

    // Process events
    for (auto &[y, type, x1, x2, idx] : events) {
        if (type == 0) {
            // Add horizontal segment to Fenwick Tree
            ft.add(x1, 1);
            ft.add(x2+1, -1);
        } else if (type == 1) {
            // Query vertical segment: x1 = x, x2 = y2
            int x = x1;
            int y1 = y, y2 = x2;
            // For all y in [y1, y2], check if there is a horizontal at (x, y)
            // But since we process by y, we only process at y1
            // So, for all horizontals at y1, if x is in [x1, x2], it's an intersection
            // But we need to process all y in [y1, y2]
            // Instead, we process all horizontals at y1, and for each vertical, we process at y1 and y2
            // So, we need to process all verticals after all horizontals are added
            // We'll process verticals separately
        } else if (type == 2) {
            // Remove horizontal segment from Fenwick Tree
            ft.add(x1, -1);
            ft.add(x2+1, 1);
        }
    }

    // For each vertical, find intersections with horizontals
    // For each vertical, for all y in [y1, y2], check if there is a horizontal at (x, y)
    // To do this efficiently, we build a map from y to list of horizontals at that y
    map<int, vector<tuple<int,int,int>>> y_to_horizontals; // y -> (x1, x2, idx)
    for (auto &[y, x1, x2, idx] : horizontals) {
        y_to_horizontals[y_map[y]].emplace_back(x_map[x1], x_map[x2], idx);
    }
    // For each vertical
    int total_lights = 0;
    for (auto &[x, y1, y2, idx] : verticals) {
        int cx = x_map[x];
        int cy1 = y_map[y1], cy2 = y_map[y2];
        for (int cy = cy1; cy <= cy2; ++cy) {
            if (y_to_horizontals.count(cy)) {
                for (auto &[hx1, hx2, hidx] : y_to_horizontals[cy]) {
                    if (hx1 <= cx && cx <= hx2) {
                        // Intersection at (x, y)
                        // Check if it's not endpoint of both segments
                        bool is_endpoint = false;
                        // For horizontal: endpoints are (x1, y), (x2, y)
                        // For vertical: endpoints are (x, y1), (x, y2)
                        if ((x == roads[hidx].x1 && cy == y_map[roads[hidx].y1]) ||
                            (x == roads[hidx].x2 && cy == y_map[roads[hidx].y2])) {
                            if ((cy == y_map[y1] && x == x_map[x]) ||
                                (cy == y_map[y2] && x == x_map[x])) {
                                is_endpoint = true;
                            }
                        }
                        if ((cy == y_map[y1] && x == x_map[x]) ||
                            (cy == y_map[y2] && x == x_map[x])) {
                            if ((x == roads[hidx].x1 && cy == y_map[roads[hidx].y1]) ||
                                (x == roads[hidx].x2 && cy == y_map[roads[hidx].y2])) {
                                is_endpoint = true;
                            }
                        }
                        // But we need to check if the intersection is not endpoint of both segments
                        // So, check if (x, y) is endpoint of both segments
                        bool is_endpoint_h = (x == roads[hidx].x1 && cy == y_map[roads[hidx].y1]) ||
                                             (x == roads[hidx].x2 && cy == y_map[roads[hidx].y2]);
                        bool is_endpoint_v = (cy == y_map[y1] && x == x_map[x]) ||
                                             (cy == y_map[y2] && x == x_map[x]);
                        if (!(is_endpoint_h && is_endpoint_v)) {
                            ++ans[hidx];
                            ++ans[idx];
                            ++total_lights;
                        }
                    }
                }
            }
        }
    }

    cout << total_lights << '\n';
    for (int i = 0; i < N; ++i) {
        cout << ans[i] << (i+1 == N ? '\n' : ' ');
    }
    return 0;
}