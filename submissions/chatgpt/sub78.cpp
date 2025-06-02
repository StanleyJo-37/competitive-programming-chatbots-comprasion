#include <iostream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

// Directions: 0 = up, 1 = up-right, 2 = right, 3 = down-right, 4 = down, 5 = down-left, 6 = left, 7 = up-left
// dx, dy for each direction (starting from up, going clockwise)
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

// To avoid visiting the same state (x, y, dir, depth) multiple times, we use a set
set<tuple<int, int, int, int>> visited_states;

// To store all unique visited cells
set<pair<int, int>> visited_cells;

// Recursive DFS function
void dfs(int x, int y, int dir, int depth, const vector<int>& t, int n) {
    // If this state was already processed, skip it
    auto state = make_tuple(x, y, dir, depth);
    if (visited_states.count(state)) return;
    visited_states.insert(state);

    int cx = x, cy = y;
    // Move t[depth] steps in the current direction, marking all cells
    for (int i = 0; i < t[depth]; ++i) {
        cx += dx[dir];
        cy += dy[dir];
        visited_cells.insert({cx, cy});
    }

    // If not at the last depth, explode and branch into two new directions
    if (depth + 1 < n) {
        // Turn left (45 degrees)
        dfs(cx, cy, (dir + 7) % 8, depth + 1, t, n);
        // Turn right (45 degrees)
        dfs(cx, cy, (dir + 1) % 8, depth + 1, t, n);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) cin >> t[i];

    // Start from (0, 0), direction up (0), depth 0
    visited_cells.insert({0, 0}); // The starting cell is always visited
    dfs(0, 0, 0, 0, t, n);

    // Output the number of unique visited cells
    cout << visited_cells.size() << endl;
    return 0;
}