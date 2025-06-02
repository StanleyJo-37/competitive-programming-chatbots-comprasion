#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store durations t_i

// Define constants for grid dimensions and coordinate mapping.
// MAX_COORD_ABS: Maximum absolute value for x or y coordinates.
// This is calculated as N * max(t_i) = 30 * 5 = 150.
const int MAX_COORD_ABS = 150;
// COORD_OFFSET: Offset to map negative coordinates to non-negative array indices.
// E.g., -150 becomes 0, 0 becomes 150, 150 becomes 300.
const int COORD_OFFSET = MAX_COORD_ABS;
// GRID_DIM: Total dimension of the grid array (e.g., 301 for range -150 to 150).
const int GRID_DIM = 2 * MAX_COORD_ABS + 1;

// Memoization table for DFS states: memo[level][x_mapped][y_mapped][direction_idx]
// 'level' goes from 1 to N (max 30), so size 31.
// 'x_mapped' and 'y_mapped' go from 0 to 300, so size 301.
// 'direction_idx' goes from 0 to 7, so size 8.
bool memo[31][GRID_DIM][GRID_DIM][8];

// Grid to store unique visited cells: visited_grid[x_mapped][y_mapped]
// This allows O(1) checking and marking of visited cells.
bool visited_grid[GRID_DIM][GRID_DIM];

// Counter for the total number of unique visited cells.
long long total_visited_cells_count = 0;

// Arrays for direction vectors (dx, dy) for 8 standard grid directions.
// Order: 0:Up, 1:Top-right, 2:Right, 3:Bottom-right, 4:Down, 5:Bottom-left, 6:Left, 7:Top-left
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

// Vector to store the durations t_1, t_2, ..., t_N.
std::vector<int> t;
// Total recursion depth N.
int N;

// Function to mark a cell as visited and increment the count if it's a new cell.
void mark_visited(int x, int y) {
    // Map grid coordinates (x, y) to array indices (mapped_x, mapped_y) using COORD_OFFSET.
    int mapped_x = x + COORD_OFFSET;
    int mapped_y = y + COORD_OFFSET;

    // Check if the cell at these mapped coordinates has not been visited yet.
    if (!visited_grid[mapped_x][mapped_y]) {
        // If it's a new cell, mark it as visited.
        visited_grid[mapped_x][mapped_y] = true;
        // Increment the total count of unique visited cells.
        total_visited_cells_count++;
    }
}

// DFS function to simulate firework movement and explosions.
// level: The current recursion level (1-indexed, from 1 to N).
// current_x, current_y: The starting coordinates of the current firework part's path segment.
// current_dir_idx: The index of the current firework part's direction.
void dfs(int level, int current_x, int current_y, int current_dir_idx) {
    // Base case: If the current level exceeds the total recursion depth N, stop.
    if (level > N) {
        return;
    }

    // Map current coordinates for memoization table lookup.
    int mapped_x = current_x + COORD_OFFSET;
    int mapped_y = current_y + COORD_OFFSET;

    // Memoization check: If this specific state (level, x, y, direction) has already been processed,
    // it means all subsequent paths from this state have already been explored and their visited cells
    // marked. So, we can return to avoid redundant computations.
    if (memo[level][mapped_x][mapped_y][current_dir_idx]) {
        return;
    }

    // Mark the current state as processed in the memoization table.
    memo[level][mapped_x][mapped_y][current_dir_idx] = true;

    // Get the length of the path segment for the current level.
    // 't' vector is 0-indexed, so t[level-1] corresponds to t_level.
    int path_length = t[level - 1];

    // Initialize path_end_x and path_end_y to the starting coordinates of the current segment.
    int path_end_x = current_x;
    int path_end_y = current_y;

    // Simulate the movement of the current firework part for 'path_length' cells.
    for (int i = 0; i < path_length; ++i) {
        // Mark the current cell in the path as visited.
        mark_visited(path_end_x, path_end_y);

        // Move to the next cell in the path.
        // This update happens for all cells except the very last one in the segment,
        // because path_end_x/y should hold the coordinates of the explosion point after the loop.
        if (i < path_length - 1) {
            path_end_x += dx[current_dir_idx];
            path_end_y += dy[current_dir_idx];
        }
    }

    // If it's the last level (N), parts explode and disappear without creating new parts.
    // So, no further recursive calls are needed.
    if (level == N) {
        return;
    }

    // Calculate the two new directions for the next level's parts.
    // One direction is 45 degrees counter-clockwise, the other is 45 degrees clockwise.
    // The modulo 8 and '+ 8' ensures the direction index wraps around correctly (0-7).
    int next_dir1 = (current_dir_idx - 1 + 8) % 8; // Counter-clockwise rotation
    int next_dir2 = (current_dir_idx + 1) % 8;     // Clockwise rotation

    // Recursively call DFS for the two new parts.
    // The new parts start from the cell *after* the explosion point in their respective new directions.
    // So, we add dx/dy of the new direction to the explosion point (path_end_x, path_end_y).
    dfs(level + 1, path_end_x + dx[next_dir1], path_end_y + dy[next_dir1], next_dir1);
    dfs(level + 1, path_end_x + dx[next_dir2], path_end_y + dy[next_dir2], next_dir2);
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read the total recursion depth N.
    std::cin >> N;

    // Resize the 't' vector to hold N durations.
    t.resize(N);
    // Read the durations t_1, t_2, ..., t_N.
    for (int i = 0; i < N; ++i) {
        std::cin >> t[i];
    }

    // Initial call to DFS:
    // Start at level 1, from coordinates (0,0), with initial direction Up (index 0).
    dfs(1, 0, 0, 0);

    // Print the total number of unique cells visited by any part of the firework.
    std::cout << total_visited_cells_count << std::endl;

    return 0; // Indicate successful execution.
}
