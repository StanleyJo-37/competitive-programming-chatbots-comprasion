#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility> // For std::pair

// Define a large enough coordinate value for segment tree.
// Coordinates are up to 10^5, so MAX_COORD should be at least 10^5.
const int MAX_COORD = 100000;

// Segment tree array. Size 4 * MAX_COORD is typical for a segment tree covering range [1, MAX_COORD].
// It stores counts of active horizontal segments at each Y-coordinate (or X-coordinate in Y-sweep).
int tree_arr[4 * (MAX_COORD + 5)]; // +5 for a small buffer

// Function to update a value in the segment tree.
// node: current node index in tree_arr.
// start, end: range covered by current node in the coordinate space.
// idx: the specific coordinate (Y or X) to update.
// val: the value to add (1 for segment start, -1 for segment end).
void update_segment_tree(int node, int start, int end, int idx, int val) {
    // If the current segment tree node represents a single point (leaf node).
    if (start == end) {
        tree_arr[node] += val;
        return;
    }
    int mid = start + (end - start) / 2; // Calculate midpoint to divide range.
    // Determine which child node to recurse into.
    if (idx <= mid) {
        update_segment_tree(2 * node, start, mid, idx, val);
    } else {
        update_segment_tree(2 * node + 1, mid + 1, end, idx, val);
    }
    // After children are updated, update the current node's value
    // by summing up its children's values.
    tree_arr[node] = tree_arr[2 * node] + tree_arr[2 * node + 1];
}

// Function to query sum in a range in the segment tree.
// node: current node index in tree_arr.
// start, end: range covered by current node.
// l, r: query range [l, r].
int query_segment_tree(int node, int start, int end, int l, int r) {
    // If the current node's range is completely outside the query range, return 0.
    if (r < start || end < l) {
        return 0;
    }
    // If the current node's range is completely within the query range, return its stored value.
    if (l <= start && end <= r) {
        return tree_arr[node];
    }
    int mid = start + (end - start) / 2; // Calculate midpoint.
    // Recurse into children and sum their results.
    int p1 = query_segment_tree(2 * node, start, mid, l, r);
    int p2 = query_segment_tree(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

// Structure to represent a road segment.
struct RoadSegment {
    int x1, y1, x2, y2;
    int id; // Original index of the segment (0 to N-1).
    bool is_horizontal; // True if y1 == y2, false if x1 == x2.
};

// Structure to represent an event for the sweep line algorithm.
struct Event {
    int coord; // The coordinate along the sweep line (X for X-sweep, Y for Y-sweep).
    int type;  // Event type: 0 for segment start, 1 for segment encountered (vertical in X-sweep, horizontal in Y-sweep), 2 for segment end.
    int other_coord_low;  // The lower bound of the segment's range in the other dimension.
    int other_coord_high; // The upper bound of the segment's range in the other dimension.
    int seg_id; // Original index of the segment.

    // Custom comparator for sorting events.
    // Events are sorted primarily by their sweep line coordinate.
    // If coordinates are equal, they are sorted by type to ensure correct processing order:
    // 0 (segment start) -> 1 (segment encountered) -> 2 (segment end).
    // This order correctly handles intersections at endpoints.
    bool operator<(const Event& other) const {
        if (coord != other.coord) {
            return coord < other.coord;
        }
        return type < other.type;
    }
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<RoadSegment> segments(N);
    // Map to store endpoint information for calculating "bad" intersections.
    // Key: (x, y) coordinate of an endpoint.
    // Value: A pair of vectors.
    //   - First vector: Stores IDs of horizontal segments that have this point as an endpoint.
    //   - Second vector: Stores IDs of vertical segments that have this point as an endpoint.
    std::map<std::pair<int, int>, std::pair<std::vector<int>, std::vector<int>>> endpoint_info;

    for (int i = 0; i < N; ++i) {
        std::cin >> segments[i].x1 >> segments[i].y1 >> segments[i].x2 >> segments[i].y2;
        segments[i].id = i;

        // Normalize coordinates so that x1 <= x2 and y1 <= y2.
        // This simplifies range queries and event creation.
        if (segments[i].x1 > segments[i].x2) {
            std::swap(segments[i].x1, segments[i].x2);
        }
        if (segments[i].y1 > segments[i].y2) {
            std::swap(segments[i].y1, segments[i].y2);
        }

        // Determine if the segment is horizontal or vertical.
        segments[i].is_horizontal = (segments[i].y1 == segments[i].y2);

        // Populate the endpoint_info map.
        // Each segment contributes its two endpoints to the map.
        if (segments[i].is_horizontal) {
            endpoint_info[{segments[i].x1, segments[i].y1}].first.push_back(i);
            endpoint_info[{segments[i].x2, segments[i].y2}].first.push_back(i);
        } else {
            endpoint_info[{segments[i].x1, segments[i].y1}].second.push_back(i);
            endpoint_info[{segments[i].x2, segments[i].y2}].second.push_back(i);
        }
    }

    // ans stores the number of traffic lights for each road segment.
    std::vector<long long> ans(N, 0);
    // total_lights_count stores the total number of traffic lights throughout Krewsko.
    long long total_lights_count = 0;

    // --- Pass 1: X-sweep to calculate raw intersections for vertical segments ---
    // This pass counts all intersections and assigns them to vertical segments.
    // It assumes all intersections are "good" (i.e., get a traffic light).
    std::vector<Event> events_x_sweep;
    for (const auto& seg : segments) {
        if (seg.is_horizontal) {
            // Horizontal segments generate start and end events along the X-axis.
            events_x_sweep.push_back({seg.x1, 0, seg.y1, seg.y1, seg.id}); // H_start event
            events_x_sweep.push_back({seg.x2, 2, seg.y1, seg.y1, seg.id}); // H_end event
        } else {
            // Vertical segments generate a single event at their X-coordinate.
            // When this event is processed, we query for intersecting horizontal segments.
            events_x_sweep.push_back({seg.x1, 1, seg.y1, seg.y2, seg.id}); // V_segment event
        }
    }
    std::sort(events_x_sweep.begin(), events_x_sweep.end());

    // Reset the segment tree for this sweep.
    // std::fill is efficient for large arrays.
    std::fill(tree_arr, tree_arr + 4 * (MAX_COORD + 5), 0);

    for (const auto& event : events_x_sweep) {
        if (event.type == 0) { // H_start event
            // A horizontal segment starts, so increment its Y-coordinate in the segment tree.
            update_segment_tree(1, 1, MAX_COORD, event.other_coord_low, 1);
        } else if (event.type == 2) { // H_end event
            // A horizontal segment ends, so decrement its Y-coordinate in the segment tree.
            update_segment_tree(1, 1, MAX_COORD, event.other_coord_low, -1);
        } else { // V_segment event
            // A vertical segment is encountered. Query the segment tree for the count of
            // active horizontal segments within this vertical segment's Y-range.
            int intersections_on_V = query_segment_tree(1, 1, MAX_COORD, event.other_coord_low, event.other_coord_high);
            // Add this count to the vertical segment's total.
            ans[event.seg_id] += intersections_on_V;
            // Add to the overall total lights count.
            total_lights_count += intersections_on_V;
        }
    }

    // --- Pass 2: Y-sweep to calculate raw intersections for horizontal segments ---
    // This pass is symmetric to Pass 1, effectively swapping the roles of X and Y axes.
    // It calculates the number of intersections for each horizontal segment.
    // The `total_lights_count` is already correctly accumulated in Pass 1 (each intersection is counted once),
    // so we do not modify it in this pass.
    std::vector<Event> events_y_sweep;
    for (const auto& seg : segments) {
        if (!seg.is_horizontal) { // Original vertical segments become "horizontal" in the Y-sweep context.
            // They generate start and end events along the Y-axis.
            events_y_sweep.push_back({seg.y1, 0, seg.x1, seg.x1, seg.id}); // V_start (now treated as H_start)
            events_y_sweep.push_back({seg.y2, 2, seg.x1, seg.x1, seg.id}); // V_end (now treated as H_end)
        } else { // Original horizontal segments become "vertical" in the Y-sweep context.
            // They generate a single event at their Y-coordinate.
            events_y_sweep.push_back({seg.y1, 1, seg.x1, seg.x2, seg.id}); // H_segment (now treated as V_segment)
        }
    }
    std::sort(events_y_sweep.begin(), events_y_sweep.end());

    // Reset the segment tree for this sweep.
    std::fill(tree_arr, tree_arr + 4 * (MAX_COORD + 5), 0);

    for (const auto& event : events_y_sweep) {
        if (event.type == 0) { // "H_start" (original V_start)
            // A segment starts, increment its X-coordinate in the segment tree.
            update_segment_tree(1, 1, MAX_COORD, event.other_coord_low, 1);
        } else if (event.type == 2) { // "H_end" (original V_end)
            // A segment ends, decrement its X-coordinate in the segment tree.
            update_segment_tree(1, 1, MAX_COORD, event.other_coord_low, -1);
        } else { // "V_segment" (original H_segment)
            // A segment is encountered. Query the segment tree for the count of
            // active "horizontal" segments (original vertical) within this segment's X-range.
            int intersections_on_H = query_segment_tree(1, 1, MAX_COORD, event.other_coord_low, event.other_coord_high);
            // Add this count to the horizontal segment's total.
            ans[event.seg_id] += intersections_on_H;
            // total_lights_count is NOT updated here.
        }
    }

    // --- Pass 3: Adjust for "bad" intersections ---
    // A "bad" intersection is one where the intersection point is an endpoint of BOTH segments.
    // These intersections should NOT have traffic lights. We subtract them from the raw counts.
    for (const auto& entry : endpoint_info) {
        const auto& point = entry.first; // The (x, y) coordinate of the endpoint.
        const auto& lists = entry.second;
        const auto& H_ids = lists.first;  // List of IDs of horizontal segments ending at 'point'.
        const auto& V_ids = lists.second; // List of IDs of vertical segments ending at 'point'.

        // If both horizontal and vertical segments end at this point,
        // then any intersection formed by a pair of such segments is a "bad" intersection.
        if (!H_ids.empty() && !V_ids.empty()) {
            // The number of "bad" intersection pairs at this specific point.
            long long num_bad_at_point = (long long)H_ids.size() * V_ids.size();
            // Subtract these bad intersections from the overall total.
            total_lights_count -= num_bad_at_point;

            // For each horizontal segment that ends at 'point', subtract the number of
            // vertical segments that end at 'point'. This accounts for the bad intersections
            // involving this horizontal segment at 'point'.
            for (int h_id : H_ids) {
                ans[h_id] -= V_ids.size();
            }
            // Similarly, for each vertical segment that ends at 'point', subtract the number of
            // horizontal segments that end at 'point'.
            for (int v_id : V_ids) {
                ans[v_id] -= H_ids.size();
            }
        }
    }

    // Output the total number of traffic lights.
    std::cout << total_lights_count << "\n";
    // Output the number of traffic lights for each road segment, separated by spaces.
    for (int i = 0; i < N; ++i) {
        std::cout << ans[i] << (i == N - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}
