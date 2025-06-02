#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Calculate total sum of the array
        long long total_sum = 0;
        for (int num : a) {
            total_sum += num;
        }

        // If the total sum is not divisible by x, the entire array is the answer
        if (total_sum % x != 0) {
            cout << n << '\n';
            continue;
        }

        // Otherwise, find the first and last elements not divisible by x
        int left = -1, right = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] % x != 0) {
                left = i;
                break;
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] % x != 0) {
                right = i;
                break;
            }
        }

        // If no such elements exist, answer is -1
        if (left == -1 && right == -1) {
            cout << -1 << '\n';
            continue;
        }

        // The longest subarray is either [left+1 ... n-1] or [0 ... right-1]
        int option1 = n - left - 1;
        int option2 = right;
        cout << max(option1, option2) << '\n';
    }

    return 0;
}