#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> rooks(m);
        // To quickly check if a cell is occupied by a rook
        vector<vector<bool>> occupied(n + 1, vector<bool>(n + 1, false));
        // To quickly check which rows and columns are occupied
        set<int> rows, cols;
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            rooks[i] = {x, y};
            occupied[x][y] = true;
            rows.insert(x);
            cols.insert(y);
        }

        bool possible = false;
        // For each rook, try to move it to any other cell in its row or column
        for (int i = 0; i < m && !possible; ++i) {
            int x = rooks[i].first;
            int y = rooks[i].second;
            // Remove this rook from the board temporarily
            occupied[x][y] = false;
            rows.erase(x);
            cols.erase(y);

            // Try all cells in the same row
            for (int ny = 1; ny <= n; ++ny) {
                if (ny == y) continue; // skip original position
                if (occupied[x][ny]) continue; // can't move to occupied cell
                // Check if any other rook is in this column
                if (cols.count(ny)) continue;
                // Valid move found
                possible = true;
                break;
            }
            // Try all cells in the same column
            for (int nx = 1; nx <= n && !possible; ++nx) {
                if (nx == x) continue; // skip original position
                if (occupied[nx][y]) continue; // can't move to occupied cell
                // Check if any other rook is in this row
                if (rows.count(nx)) continue;
                // Valid move found
                possible = true;
                break;
            }

            // Restore the rook
            occupied[x][y] = true;
            rows.insert(x);
            cols.insert(y);
        }

        cout << (possible ? "YES" : "NO") << endl;
    }
    return 0;
}