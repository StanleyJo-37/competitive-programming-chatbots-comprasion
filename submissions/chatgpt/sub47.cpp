#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, k;
    // Read number of planks and width of the hole
    cin >> n >> k;
    vector<int> h(n);
    // Read the heights of the planks
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // Initialize sum of the first k planks
    int current_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_sum += h[i];
    }

    int min_sum = current_sum; // Store the minimum sum found so far
    int min_index = 0; // Store the starting index (0-based) of the minimum sum window

    // Use sliding window to find the minimum sum of k consecutive planks
    for (int i = 1; i <= n - k; ++i) {
        // Subtract the plank that is leaving the window and add the new plank
        current_sum = current_sum - h[i - 1] + h[i + k - 1];
        // If a new minimum is found, update min_sum and min_index
        if (current_sum < min_sum) {
            min_sum = current_sum;
            min_index = i;
        }
    }

    // Output the 1-based index of the first plank in the optimal window
    cout << (min_index + 1) << endl;

    return 0;
}