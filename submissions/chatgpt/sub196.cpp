#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // For each residue class mod k, collect the elements
        vector<vector<long long>> groups(k);
        for (int i = 0; i < n; ++i) {
            groups[i % k].push_back(a[i]);
        }

        // Sort each group in descending order so we can put the largest elements in the front
        for (int r = 0; r < k; ++r) {
            sort(groups[r].rbegin(), groups[r].rend());
        }

        // Reconstruct the array: for each position i, pick the largest available from its group
        vector<long long> b(n);
        vector<int> idx(k, 0); // index for each group
        for (int i = 0; i < n; ++i) {
            int r = i % k;
            b[i] = groups[r][idx[r]++];
        }

        // Now, find the maximum sum of k consecutive elements in b
        long long max_sum = 0, curr_sum = 0;
        for (int i = 0; i < k; ++i) curr_sum += b[i];
        max_sum = curr_sum;
        for (int i = k; i < n; ++i) {
            curr_sum += b[i] - b[i - k];
            if (curr_sum > max_sum) max_sum = curr_sum;
        }

        cout << max_sum << '\n';
    }
    return 0;
}