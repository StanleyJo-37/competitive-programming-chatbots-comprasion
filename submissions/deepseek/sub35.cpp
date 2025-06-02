#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Calculate the initial sum without any reversal
    long long original_sum = 0;
    for (int i = 0; i < n; ++i) original_sum += a[i] * b[i];
    long long max_sum = original_sum;

    // Check all possible subarrays to reverse and find the maximum gain
    for (int center = 0; center < n; ++center) {
        // Odd length subarrays centered at 'center'
        long long current_sum = original_sum;
        for (int l = center, r = center; l >= 0 && r < n; --l, ++r) {
            current_sum -= a[l] * b[l] + a[r] * b[r];
            current_sum += a[l] * b[r] + a[r] * b[l];
            if (current_sum > max_sum) max_sum = current_sum;
        }
        // Even length subarrays centered between 'center' and 'center+1'
        current_sum = original_sum;
        for (int l = center, r = center + 1; l >= 0 && r < n; --l, ++r) {
            current_sum -= a[l] * b[l] + a[r] * b[r];
            current_sum += a[l] * b[r] + a[r] * b[l];
            if (current_sum > max_sum) max_sum = current_sum;
        }
    }

    cout << max_sum << endl;
    return 0;
}