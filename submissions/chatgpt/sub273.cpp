#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        int total_sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total_sum += a[i];
        }

        // If the sum of the whole array is not divisible by x, the answer is n
        if (total_sum % x != 0) {
            cout << n << '\n';
            continue;
        }

        // Otherwise, try to remove the minimal prefix or suffix so that the sum is not divisible by x
        int left = -1, right = -1;
        // Find from left the first element not divisible by x
        for (int i = 0; i < n; ++i) {
            if (a[i] % x != 0) {
                left = i;
                break;
            }
        }
        // Find from right the first element not divisible by x
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] % x != 0) {
                right = n - 1 - i;
                break;
            }
        }

        // If all elements are divisible by x, it's impossible
        if (left == -1 && right == -1) {
            cout << -1 << '\n';
        } else {
            // Remove minimal prefix or suffix, so answer is n - min(left+1, right+1)
            // But since we want the maximal subarray, we remove the minimal number of elements
            // So, answer is n - min(left+1, right+1) = max(n - (left+1), n - (right+1))
            // But since we can remove either prefix or suffix, the answer is n - min(left, right) - 1
            // Actually, the correct answer is max(n - (left + 1), n - (right + 1))
            cout << max(n - (left + 1), n - (right + 1)) << '\n';
        }
    }
    return 0;
}