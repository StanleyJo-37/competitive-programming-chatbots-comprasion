#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

struct Road {
    int x1, y1, x2, y2;
    bool is_horizontal;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Road> roads(N);
    vector<int> horizontal_y;
    unordered_map<int, vector<pair<int, int>>> vertical_segments; // key: x, value: list of (y1, y2)

    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            roads[i] = {x1, min(y1, y2), x2, max(y1, y2), false};
            vertical_segments[x1].emplace_back(min(y1, y2), max(y1, y2));
        } else {
            roads[i] = {min(x1, x2), y1, max(x1, x2), y2, true};
            horizontal_y.push_back(y1);
        }
    }

    // Sort horizontal y's for binary search
    sort(horizontal_y.begin(), horizontal_y.end());
    horizontal_y.erase(unique(horizontal_y.begin(), horizontal_y.end()), horizontal_y.end());

    // Process vertical segments: sort and merge overlapping/adjacent segments
    for (auto& entry : vertical_segments) {
        auto& segments = entry.second;
        sort(segments.begin(), segments.end());
        vector<pair<int, int>> merged;
        for (const auto& seg : segments) {
            if (merged.empty()) {
                merged.push_back(seg);
            } else {
                auto& last = merged.back();
                if (seg.first <= last.second) {
                    last.second = max(last.second, seg.second);
                } else {
                    merged.push_back(seg);
                }
            }
        }
        segments = merged;
    }

    // Build a list of all vertical x's for binary search
    vector<int> vertical_x;
    for (const auto& entry : vertical_segments) {
        vertical_x.push_back(entry.first);
    }
    sort(vertical_x.begin(), vertical_x.end());

    // For each horizontal road, count intersections with vertical roads
    vector<int> road_counts(N, 0);
    int total_lights = 0;

    for (int i = 0; i < N; ++i) {
        if (!roads[i].is_horizontal) continue;
        int y = roads[i].y1;
        int x1 = roads[i].x1;
        int x2 = roads[i].x2;

        // Find all vertical x's in [x1, x2]
        auto lower = lower_bound(vertical_x.begin(), vertical_x.end(), x1);
        auto upper = upper_bound(vertical_x.begin(), vertical_x.end(), x2);
        for (auto it = lower; it != upper; ++it) {
            int x = *it;
            const auto& segments = vertical_segments[x];
            // Check if any segment in vertical x contains y
            auto seg_it = lower_bound(segments.begin(), segments.end(), make_pair(y, y),
                [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.second < b.first;
                });
            if (seg_it != segments.end() && seg_it->first <= y && y <= seg_it->second) {
                // Check if intersection is not an endpoint of both segments
                bool is_h_endpoint = (x == x1 || x == x2);
                bool is_v_endpoint = (y == seg_it->first || y == seg_it->second);
                if (!is_h_endpoint || !is_v_endpoint) {
                    road_counts[i]++;
                    total_lights++;
                }
            }
        }
    }

    // For each vertical road, count intersections with horizontal roads
    for (int i = 0; i < N; ++i) {
        if (roads[i].is_horizontal) continue;
        int x = roads[i].x1;
        int y1 = roads[i].y1;
        int y2 = roads[i].y2;

        // Check if x is in any horizontal road's x range and y is in horizontal's y
        auto y_it = lower_bound(horizontal_y.begin(), horizontal_y.end(), y1);
        while (y_it != horizontal_y.end() && *y_it <= y2) {
            int y = *y_it;
            // Check if y is not an endpoint of vertical segment
            bool is_v_endpoint = (y == y1 || y == y2);
            // Find horizontal roads with y and x in [x1, x2]
            for (int j = 0; j < N; ++j) {
                if (!roads[j].is_horizontal) continue;
                if (roads[j].y1 != y) continue;
                if (roads[j].x1 <= x && x <= roads[j].x2) {
                    bool is_h_endpoint = (x == roads[j].x1 || x == roads[j].x2);
                    if (!is_h_endpoint || !is_v_endpoint) {
                        road_counts[j]++;
                        total_lights++;
                    }
                }
            }
            ++y_it;
        }
    }

    // The above counts double-counts intersections, so divide total_lights by 2
    total_lights /= 2;
    // Also, road_counts[i] is double-counted for horizontal roads, so adjust
    for (int i = 0; i < N; ++i) {
        if (roads[i].is_horizontal) {
            road_counts[i] /= 2;
        }
    }

    cout << total_lights << "\n";
    for (int i = 0; i < N; ++i) {
        if (i > 0) cout << " ";
        cout << road_counts[i];
    }
    cout << "\n";

    return 0;
}