#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n, m;
        cin >> n >> m; // Matrix dimensions

        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> a[i][j]; // Read matrix

        long long total_cost = 0;

        // For each group of symmetric positions, process only once
        // Each group consists of positions that are symmetric with respect to both row and column palindromes
        // For each position (i, j), its symmetric positions are:
        // (i, j), (i, m-j-1), (n-i-1, j), (n-i-1, m-j-1)
        // We only need to process the top-left quarter (including the center row/column if n or m is odd)
        for (int i = 0; i <= (n - 1) / 2; ++i) {
            for (int j = 0; j <= (m - 1) / 2; ++j) {
                // Collect all symmetric positions in this group
                vector<int> vals;
                vals.push_back(a[i][j]);
                if (j != m - j - 1) vals.push_back(a[i][m - j - 1]);
                if (i != n - i - 1) vals.push_back(a[n - i - 1][j]);
                if (i != n - i - 1 && j != m - j - 1) vals.push_back(a[n - i - 1][m - j - 1]);

                // To minimize the sum of absolute differences, set all to the median
                sort(vals.begin(), vals.end());
                int median = vals[vals.size() / 2];

                // Sum the cost to make all values in the group equal to the median
                for (int v : vals)
                    total_cost += abs(v - median);
            }
        }

        cout << total_cost << '\n';
    }

    return 0;
}