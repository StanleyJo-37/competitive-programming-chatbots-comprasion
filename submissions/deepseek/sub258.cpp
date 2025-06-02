#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Precompute prefix max and suffix max
    vector<int> prefix_max(n), suffix_max(n);
    prefix_max[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefix_max[i] = max(prefix_max[i-1], a[i]);
    }
    suffix_max[n-1] = a[n-1];
    for (int i = n-2; i >= 0; --i) {
        suffix_max[i] = max(suffix_max[i+1], a[i]);
    }

    // Precompute min in the middle part using a sliding window approach
    // We'll use a deque to maintain the min in the middle part
    // But since we need to find min in [x+1, x+y], we can use a sliding window approach
    // However, it's tricky to handle all possible y's, so we'll try to find x and z first

    // The target value must be the min of the entire array, but that's not necessarily true
    // So, we need to find a value that is the max of the first part, min of the middle, and max of the third part
    // Let's denote this value as 'target'

    // Iterate all possible x (1 to n-2)
    for (int x = 1; x <= n-2; ++x) {
        int target = prefix_max[x-1];
        // Now, find if there exists a z >=1 such that x + y + z = n and y >=1
        // So, y = n - x - z >=1 => z <= n - x -1
        // Also, suffix_max[x + y] = target, where y = n - x - z
        // So, suffix_max[n - z] = target
        // So, we need to find z such that suffix_max[n - z] == target and z >=1 and x + y + z = n and y >=1

        // Binary search for z in [1, n - x -1]
        int low_z = 1, high_z = n - x -1;
        int best_z = -1;
        while (low_z <= high_z) {
            int mid_z = (low_z + high_z) / 2;
            int current_suffix_max = suffix_max[n - mid_z];
            if (current_suffix_max == target) {
                best_z = mid_z;
                low_z = mid_z + 1; // try to find larger z (smaller y)
            } else if (current_suffix_max < target) {
                high_z = mid_z - 1;
            } else {
                low_z = mid_z + 1;
            }
        }
        if (best_z != -1) {
            int y = n - x - best_z;
            if (y >= 1) {
                // Now, check if min(x+1, x+y) == target
                // We need to find the min in the range [x, x+y-1] (0-based)
                // To find this efficiently, we can use a segment tree or sparse table
                // Here, we'll use a simple approach since n is up to 2e5 and t is 2e4, but sum of n is 2e5
                // So, O(n) per test case is acceptable
                int min_middle = a[x];
                for (int i = x + 1; i < x + y; ++i) {
                    min_middle = min(min_middle, a[i]);
                }
                if (min_middle == target) {
                    cout << "YES\n";
                    cout << x << " " << y << " " << best_z << "\n";
                    return;
                }
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}