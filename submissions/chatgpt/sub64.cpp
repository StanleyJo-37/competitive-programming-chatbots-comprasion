#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    // Create a vector representing the indices of the digits
    vector<int> perm(k);
    for (int i = 0; i < k; ++i) perm[i] = i;

    int min_diff = INT_MAX;

    // Try all possible permutations of digit positions
    do {
        int min_val = INT_MAX;
        int max_val = INT_MIN;

        // For each number, rearrange its digits according to the current permutation
        for (int i = 0; i < n; ++i) {
            string rearranged = "";
            for (int j = 0; j < k; ++j) {
                rearranged += nums[i][perm[j]];
            }
            // Convert rearranged string to integer (leading zeros are allowed)
            int val = stoi(rearranged);
            min_val = min(min_val, val);
            max_val = max(max_val, val);
        }
        // Update the minimal possible difference
        min_diff = min(min_diff, max_val - min_val);
    } while (next_permutation(perm.begin(), perm.end()));

    cout << min_diff << endl;
    return 0;
}