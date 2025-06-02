#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // Compute the prefix sum array to efficiently calculate the sum of any k consecutive planks
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + h[i - 1];
    }

    int min_sum = INT_MAX;
    int best_start = 0;

    // Iterate through all possible starting positions of the k consecutive planks
    for (int i = 0; i <= n - k; ++i) {
        int current_sum = prefix[i + k] - prefix[i];
        if (current_sum < min_sum) {
            min_sum = current_sum;
            best_start = i;
        }
    }

    // The problem uses 1-based indexing, so add 1 to the 0-based index
    cout << best_start + 1 << endl;

    return 0;
}