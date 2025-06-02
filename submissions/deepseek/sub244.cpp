#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i]; // Convert to 0-based index
    }

    vector<bool> in_circulation(n, false);
    vector<int> res(n + 1);
    res[0] = 1; // Initial state: all O's, hardness is 1 (no swaps needed)

    int max_group = 0;
    for (int i = 0; i < n; ++i) {
        int pos = p[i];
        in_circulation[pos] = true;
        // Check left and right neighbors to form groups
        int left = (pos > 0 && in_circulation[pos - 1]) ? 1 : 0;
        int right = (pos < n - 1 && in_circulation[pos + 1]) ? 1 : 0;
        
        if (left && right) {
            // Merging two groups into one
            max_group -= 2;
            res[i + 1] = (i + 2) - max_group;
        } else if (left || right) {
            // Extending a group by one
            max_group -= 1;
            res[i + 1] = (i + 2) - max_group;
        } else {
            // Creating a new group
            max_group += 1;
            res[i + 1] = (i + 2) - max_group;
        }
    }

    for (int i = 0; i <= n; ++i) {
        cout << res[i] << (i < n ? ' ' : '\n');
    }

    return 0;
}