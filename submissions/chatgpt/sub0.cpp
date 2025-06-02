#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n; // Read the number of problems
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; // Read the difficulties
    }

    // We use a two-pointer (sliding window) approach.
    // For each right pointer, we find the leftmost position such that
    // a[right] <= 2 * a[left]. The window [left, right] is a valid contest.
    int left = 0;
    int max_len = 1; // At least one problem can always be chosen
    for (int right = 0; right < n; ++right) {
        // Move left pointer forward if the window is invalid
        while (a[right] > 2 * a[left]) {
            ++left;
        }
        // Update the maximum length found so far
        max_len = max(max_len, right - left + 1);
    }

    cout << max_len << endl; // Output the answer
    return 0;
}