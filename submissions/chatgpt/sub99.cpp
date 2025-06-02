#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input dimensions
    int n, m;
    cin >> n >> m;

    // Read the table and store good cells
    vector<pair<int, int>> good_cells;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int a;
            cin >> a;
            // If cell is good and not a corner, store it
            if (a == 1) {
                // Corners are (1,1), (1,m), (n,1), (n,m)
                if (!((i == 1 || i == n) && (j == 1 || j == m))) {
                    good_cells.emplace_back(i, j);
                }
            }
        }
    }

    // There are 4 corners
    vector<pair<int, int>> corners = {
        {1, 1},
        {1, m},
        {n, 1},
        {n, m}
    };

    // The minimum number of operations needed is the minimum number of good cells
    // needed to cover the table using rectangles with one good cell and one corner.
    // For each good cell, it can cover a rectangle with any corner.
    // The optimal way is to try all possible pairs of good cells and corners,
    // but since each good cell can be paired with all 4 corners, and the rectangles
    // always overlap at the good cell, the minimum number of operations is:
    // - If there is only one good cell, answer is 4 (one for each corner).
    // - If there are multiple good cells, we can use each to cover a part of the table,
    //   and the minimum number of operations is the minimal number of good cells needed
    //   to cover the table with rectangles to all corners.

    // For this problem, the answer is:
    // - If there is only one good cell, answer is 4.
    // - Otherwise, answer is the minimal number of good cells needed to cover all 4 corners
    //   (since each good cell can be paired with a corner to cover a rectangle).
    // - But since no good cell is a corner, and the rectangles always cover the corner and the good cell,
    //   the minimum number of operations is the minimal number of good cells such that for each corner,
    //   there is a good cell not in that corner's row or column (since good cells can't be corners).

    // For each corner, we need at least one good cell not in its row or column.
    // So, for each corner, check if there is a good cell not in its row or column.
    // If for all corners, there is a good cell not in its row or column, then answer is 2.
    // Otherwise, answer is 4.

    // For each corner, check if there is a good cell not in its row or column
    int min_ops = 4;
    for (int mask = 1; mask < (1 << good_cells.size()); ++mask) {
        // For each subset of good cells
        vector<pair<int, int>> subset;
        for (int i = 0; i < good_cells.size(); ++i) {
            if (mask & (1 << i)) {
                subset.push_back(good_cells[i]);
            }
        }
        // For each corner, check if there is a good cell in subset not in its row or column
        bool ok = true;
        for (auto& corner : corners) {
            bool found = false;
            for (auto& cell : subset) {
                if (cell.first != corner.first && cell.second != corner.second) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                ok = false;
                break;
            }
        }
        if (ok) {
            min_ops = min(min_ops, (int)subset.size());
        }
    }

    // If only one good cell, answer is 4
    if (good_cells.size() == 1) min_ops = 4;

    cout << min_ops << endl;
    return 0;
}