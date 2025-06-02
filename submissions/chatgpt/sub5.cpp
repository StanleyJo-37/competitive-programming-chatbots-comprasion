#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(2);
        cin >> grid[0] >> grid[1];

        // Visited array to keep track of visited cells
        bool visited[2][105] = {false};

        // BFS queue: each element is a pair (row, col)
        queue<pair<int, int>> q;
        q.push({0, 0}); // Start at (1,1) which is (0,0) in 0-based indexing
        visited[0][0] = true;

        // Directions: 8 possible moves (including diagonals)
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        bool found = false;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            // If we reach (2, n) which is (1, n-1) in 0-based
            if (x == 1 && y == n - 1) {
                found = true;
                break;
            }

            // Try all 8 directions
            for (int d = 0; d < 8; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                // Check bounds
                if (nx >= 0 && nx < 2 && ny >= 0 && ny < n) {
                    // If not visited and not a trap
                    if (!visited[nx][ny] && grid[nx][ny] == '0') {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }

        // Output result for this test case
        cout << (found ? "YES" : "NO") << endl;
    }
    return 0;
}