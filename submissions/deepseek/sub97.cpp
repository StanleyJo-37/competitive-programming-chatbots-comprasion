#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> matrix(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> matrix[i][j];
            }
        }

        long long total_operations = 0;
        // Iterate over each group of symmetric positions
        for (int i = 0; i < (n + 1) / 2; ++i) {
            for (int j = 0; j < (m + 1) / 2; ++j) {
                // Collect all symmetric elements
                vector<int> elements;
                elements.push_back(matrix[i][j]);
                // Check if the current column has a symmetric column
                if (j != m - 1 - j) {
                    elements.push_back(matrix[i][m - 1 - j]);
                }
                // Check if the current row has a symmetric row
                if (i != n - 1 - i) {
                    elements.push_back(matrix[n - 1 - i][j]);
                    // Check if the symmetric column also has a symmetric row
                    if (j != m - 1 - j) {
                        elements.push_back(matrix[n - 1 - i][m - 1 - j]);
                    }
                }
                // Find the median to minimize the total operations
                sort(elements.begin(), elements.end());
                int median = elements[elements.size() / 2];
                // Calculate the total operations for this group
                for (int num : elements) {
                    total_operations += abs(num - median);
                }
            }
        }
        cout << total_operations << endl;
    }
    return 0;
}