#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to check if the level can be completed using BFS
bool canCompleteLevel(const vector<string>& grid, int n) {
    // Directions for all 8 possible moves (including diagonals)
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    // Visited matrix to keep track of visited cells
    vector<vector<bool>> visited(2, vector<bool>(n, false));
    queue<pair<int, int>> q;
    
    // Start from (0, 0) since grid is 0-indexed for easier access
    q.push({0, 0});
    visited[0][0] = true;
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        
        // Check if reached the destination (2, n) which is (1, n-1) in 0-index
        if (x == 1 && y == n - 1) {
            return true;
        }
        
        // Explore all 8 possible moves
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Check if the new position is within bounds and not a trap and not visited
            if (nx >= 0 && nx < 2 && ny >= 0 && ny < n && grid[nx][ny] == '0' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(2);
        cin >> grid[0] >> grid[1];
        
        if (canCompleteLevel(grid, n)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}