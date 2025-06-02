#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    
    // Read the grid and check if any good cell is in the first/last row or column
    bool firstRowGood = false, lastRowGood = false;
    bool firstColGood = false, lastColGood = false;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                if (i == 0) firstRowGood = true;
                if (i == n - 1) lastRowGood = true;
                if (j == 0) firstColGood = true;
                if (j == m - 1) lastColGood = true;
            }
        }
    }
    
    // If any good cell is on the border (first/last row or column), then answer is 2
    if (firstRowGood || lastRowGood || firstColGood || lastColGood) {
        cout << 2 << endl;
    } else {
        // Otherwise, answer is 4 (as in the first sample)
        cout << 4 << endl;
    }
    
    return 0;
}