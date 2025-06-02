#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // The key observation is that each swap flips the direction of both swapped elements.
    // To end with all directions right, the number of flips for each element must be even.
    // This means the parity of the number of times each element is moved must be even.
    // For the array to be sorted, the relative order of elements must be correct.
    // For elements with the same value, their relative order must not change because
    // swapping them would require an odd number of flips (since they are adjacent and same value),
    // leading to a direction flip, which is not allowed (must end with all right).
    
    // So, the solution is possible if and only if:
    // 1. The array can be sorted (non-decreasing).
    // 2. For every value, the count of it in the original array is the same as in the sorted array.
    // 3. For elements with the same value, their positions in the original array must have the same parity (even or odd indices) as in the sorted array.
    // Because swapping same-value elements would flip their directions, which is not allowed unless the flips cancel out (even number).
    
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    // Check if the array can be sorted (condition 1 and 2)
    for (int i = 0; i < n; ++i) {
        if (a[i] != sorted_a[i]) {
            // Check if the sorted array is non-decreasing and matches the original's elements
            cout << "NO\n";
            return;
        }
    }
    
    // Now, check for same-value elements' parity (condition 3)
    // For each value, the original positions and sorted positions must have matching parities.
    // We can group positions by value and check parity consistency.
    unordered_map<int, vector<int>> original_pos, sorted_pos;
    for (int i = 0; i < n; ++i) {
        original_pos[a[i]].push_back(i % 2);
        sorted_pos[sorted_a[i]].push_back(i % 2);
    }
    
    for (auto& [val, positions] : original_pos) {
        auto& sorted_positions = sorted_pos[val];
        // Count the number of even and odd positions in original and sorted arrays
        int original_evens = count(positions.begin(), positions.end(), 0);
        int sorted_evens = count(sorted_positions.begin(), sorted_positions.end(), 0);
        if (original_evens != sorted_evens) {
            cout << "NO\n";
            return;
        }
    }
    
    cout << "YES\n";
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