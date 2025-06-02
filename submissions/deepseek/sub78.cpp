#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    // Directions: 0=up, 1=top-left, 2=top-right, etc.
    // Using a set to store visited coordinates (x, y)
    set<pair<int, int>> visited;

    // Each element in the queue is (x, y, direction, remaining steps, current level)
    // Direction mapping: 0=up, 1=top-left, 2=top-right
    // For each level, we process all segments and split them into two new directions
    vector<tuple<int, int, int, int, int>> segments;

    // Initial segment: starts at (0, 0), moves up (dir=0), t[0] steps, level 0
    segments.emplace_back(0, 0, 0, t[0], 0);

    while (!segments.empty()) {
        vector<tuple<int, int, int, int, int>> next_segments;
        for (auto [x, y, dir, steps, level] : segments) {
            int dx = 0, dy = 0;
            // Determine direction offsets
            if (dir == 0) { // up
                dy = 1;
            } else if (dir == 1) { // top-left
                dx = -1;
                dy = 1;
            } else if (dir == 2) { // top-right
                dx = 1;
                dy = 1;
            }

            // Mark all cells in this segment
            for (int i = 0; i < steps; ++i) {
                visited.emplace(x + i * dx, y + i * dy);
            }

            // If not the last level, split into two new segments
            if (level + 1 < n) {
                int new_x = x + (steps - 1) * dx;
                int new_y = y + (steps - 1) * dy;
                // New directions: (dir - 1) mod 3 and (dir + 1) mod 3
                int new_dir1 = (dir + 1) % 4;
                int new_dir2 = (dir - 1 + 4) % 4;
                // Ensure directions are within 0-3 (handling wrap-around)
                // But for n=30, directions can be more than 4, but the problem says 45 degrees, so:
                // Directions: 0=up, 1=top-left, 2=left, 3=bottom-left, etc.
                // But the problem description implies only 3 directions: up, top-left, top-right.
                // So, we need to adjust the direction handling.
                // Based on the note, after up, it splits into top-left and top-right.
                // So, directions are:
                // 0: up
                // 1: top-left
                // 2: top-right
                // Then, top-left splits into left (dir=3) and up (dir=0)
                // top-right splits into up (dir=0) and right (dir=4)
                // But this complicates things. Maybe better to represent directions as angles.
                // Alternative approach: represent directions as dx, dy pairs.
                // For initial direction (0,1), splits into (-1,1) and (1,1).
                // Then (-1,1) splits into (-1,0) and (0,1).
                // (1,1) splits into (0,1) and (1,0).
                // So, each split turns 45 degrees left or right.
                // So, for a direction (dx, dy), left turn is (dx*0 - dy*1, dx*1 + dy*0) = (-dy, dx)
                // Right turn is (dx*0 + dy*1, -dx*1 + dy*0) = (dy, -dx)
                // So, we can represent directions as (dx, dy) pairs.
                // Let's refactor the code to use (dx, dy) pairs instead of dir numbers.

                // Refactored approach: represent direction as (dx, dy)
                pair<int, int> direction;
                if (dir == 0) direction = {0, 1}; // up
                else if (dir == 1) direction = {-1, 1}; // top-left
                else if (dir == 2) direction = {1, 1}; // top-right

                // Calculate new directions: left and right 45-degree turns
                pair<int, int> new_dir1 = {-direction.second, direction.first}; // left turn
                pair<int, int> new_dir2 = {direction.second, -direction.first}; // right turn

                // Convert new_dir1 and new_dir2 back to dir numbers (0-2)
                int nd1;
                if (new_dir1.first == 0 && new_dir1.second == 1) nd1 = 0;
                else if (new_dir1.first == -1 && new_dir1.second == 1) nd1 = 1;
                else if (new_dir1.first == 1 && new_dir1.second == 1) nd1 = 2;
                else if (new_dir1.first == -1 && new_dir1.second == 0) nd1 = 3;
                else if (new_dir1.first == 0 && new_dir1.second == -1) nd1 = 4;
                else if (new_dir1.first == 1 && new_dir1.second == 0) nd1 = 5;
                else nd1 = 6; // should not happen for n <= 30

                int nd2;
                if (new_dir2.first == 0 && new_dir2.second == 1) nd2 = 0;
                else if (new_dir2.first == -1 && new_dir2.second == 1) nd2 = 1;
                else if (new_dir2.first == 1 && new_dir2.second == 1) nd2 = 2;
                else if (new_dir2.first == -1 && new_dir2.second == 0) nd2 = 3;
                else if (new_dir2.first == 0 && new_dir2.second == -1) nd2 = 4;
                else if (new_dir2.first == 1 && new_dir2.second == 0) nd2 = 5;
                else nd2 = 6; // should not happen for n <= 30

                next_segments.emplace_back(new_x, new_y, nd1, t[level + 1], level + 1);
                next_segments.emplace_back(new_x, new_y, nd2, t[level + 1], level + 1);
            }
        }
        segments = next_segments;
    }

    cout << visited.size() << endl;
    return 0;
}