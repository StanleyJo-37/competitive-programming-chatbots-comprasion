#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        vector<int> a(n);
        int total_sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total_sum += a[i];
        }

        // If the total sum is less than s, it's impossible to get sum s
        if (total_sum < s) {
            cout << -1 << '\n';
            continue;
        }
        // If the total sum is exactly s, no need to remove anything
        if (total_sum == s) {
            cout << 0 << '\n';
            continue;
        }

        // We need to remove (total_sum - s) ones from the array by removing from the ends
        // The problem reduces to: Find the longest subarray with sum == s
        // The answer is n - (length of that subarray)
        int max_len = -1;
        int left = 0, curr_sum = 0;
        for (int right = 0; right < n; ++right) {
            curr_sum += a[right];
            // Shrink window from the left if sum > s
            while (left <= right && curr_sum > s) {
                curr_sum -= a[left];
                ++left;
            }
            // If current window sum is exactly s, update max_len
            if (curr_sum == s) {
                int len = right - left + 1;
                if (len > max_len) max_len = len;
            }
        }
        // If we never found such a subarray, it's impossible
        if (max_len == -1) {
            cout << -1 << '\n';
        } else {
            cout << n - max_len << '\n';
        }
    }
    return 0;
}