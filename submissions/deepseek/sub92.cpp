#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        set<int> rows, cols;
        vector<pair<int, int>> rooks(m);
        
        // Read rook positions and track occupied rows and columns
        for (int i = 0; i < m; ++i) {
            cin >> rooks[i].first >> rooks[i].second;
            rows.insert(rooks[i].first);
            cols.insert(rooks[i].second);
        }
        
        bool possible = false;
        
        // Check for each rook if there's a valid move
        for (int i = 0; i < m && !possible; ++i) {
            int x = rooks[i].first, y = rooks[i].second;
            
            // Check if there's any unoccupied row in the same column
            for (int r = 1; r <= n; ++r) {
                if (rows.find(r) == rows.end()) {
                    possible = true;
                    break;
                }
            }
            if (possible) break;
            
            // Check if there's any unoccupied column in the same row
            for (int c = 1; c <= n; ++c) {
                if (cols.find(c) == cols.end()) {
                    possible = true;
                    break;
                }
            }
        }
        
        cout << (possible ? "YES" : "NO") << endl;
    }
    return 0;
}