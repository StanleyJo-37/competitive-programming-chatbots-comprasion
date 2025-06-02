#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // The idea is to find the longest contiguous non-decreasing subsequence where
    // the elements are in the same relative order as in the sorted array.
    // The answer will then be n - length of this subsequence.
    
    // Create a sorted version of the array to compare against.
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    // We'll use a map to track the positions of each value in the original array.
    // Since there can be duplicates, we'll store the indices in a vector for each value.
    unordered_map<int, vector<int>> positions;
    for (int i = 0; i < n; ++i) {
        positions[a[i]].push_back(i);
    }
    
    // For each value in the sorted array, we need to process them in order.
    // We'll track the maximum possible length of a contiguous subsequence in the original array
    // that matches the sorted array's order.
    int max_len = 0;
    int current_len = 0;
    int last_pos = -1;
    
    for (int i = 0; i < n; ) {
        int val = sorted_a[i];
        // Find all consecutive occurrences of 'val' in the sorted array.
        int j = i;
        while (j < n && sorted_a[j] == val) {
            ++j;
        }
        int count = j - i;
        
        // Now, in the original array, we need to find 'count' occurrences of 'val'
        // that come after 'last_pos' in the original array.
        auto& pos_list = positions[val];
        // Binary search for the first position in pos_list that is > last_pos.
        auto it = upper_bound(pos_list.begin(), pos_list.end(), last_pos);
        if (it == pos_list.end()) {
            // No such positions left, reset the current_len.
            current_len = 0;
            last_pos = -1;
            i = j; // Move to next value in sorted array.
            continue;
        }
        int start_idx = it - pos_list.begin();
        if (start_idx + count - 1 >= pos_list.size()) {
            // Not enough elements left to form the contiguous block.
            current_len = 0;
            last_pos = -1;
            i = j;
            continue;
        }
        // The last position in this block is pos_list[start_idx + count - 1].
        int new_last_pos = pos_list[start_idx + count - 1];
        current_len += count;
        max_len = max(max_len, current_len);
        last_pos = new_last_pos;
        i = j;
    }
    
    cout << n - max_len << '\n';
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