#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // Map to count occurrences of each number in the current window
    unordered_map<int, int> freq;
    int distinct = 0; // Number of distinct elements in the current window
    int l = 0, r = 0; // Window pointers (0-based)
    int ans_l = -1, ans_r = -1; // Store the answer (1-based)
    bool found = false;

    // Use two pointers to find the minimal by inclusion segment
    while (r < n) {
        // Expand the window to the right
        if (freq[a[r]] == 0) distinct++;
        freq[a[r]]++;
        r++;

        // When we have at least k distinct numbers, try to shrink from the left
        while (distinct > k) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) distinct--;
            l++;
        }

        // When we have exactly k distinct numbers, try to minimize the window from the left
        if (distinct == k) {
            // Try to shrink as much as possible while keeping k distinct numbers
            while (freq[a[l]] > 1) {
                freq[a[l]]--;
                l++;
            }
            // Store the answer (convert to 1-based indices)
            if (!found) {
                ans_l = l + 1;
                ans_r = r;
                found = true;
            }
        }
    }

    if (found) {
        cout << ans_l << " " << ans_r << "\n";
    } else {
        cout << "-1 -1\n";
    }

    return 0;
}