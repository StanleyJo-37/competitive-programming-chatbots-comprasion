#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // For each group i mod k, we can swap elements within the group.
        // To maximize the sum of k consecutive elements, we need to maximize
        // the sum of the top elements in each group. The optimal way is to
        // sort each group in descending order and pick the largest elements.
        vector<vector<int>> groups(k);
        for (int i = 0; i < n; ++i) {
            groups[i % k].push_back(a[i]);
        }

        // Sort each group in descending order
        for (int i = 0; i < k; ++i) {
            sort(groups[i].rbegin(), groups[i].rend());
        }

        // Reconstruct the array by picking the largest elements from each group
        vector<int> new_a(n);
        for (int i = 0; i < n; ++i) {
            new_a[i] = groups[i % k][i / k];
        }

        // Now find the maximum sum of k consecutive elements in the new array
        long long max_sum = 0;
        long long current_sum = 0;
        for (int i = 0; i < k; ++i) {
            current_sum += new_a[i];
        }
        max_sum = current_sum;
        for (int i = k; i < n; ++i) {
            current_sum += new_a[i] - new_a[i - k];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }

        cout << max_sum << endl;
    }
    return 0;
}