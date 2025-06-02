#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Calculate the total sum of the array
    long long total_sum = accumulate(a.begin(), a.end(), 0LL);

    // If the total sum is not divisible by 3, there's no possible split
    if (total_sum % 3 != 0) {
        cout << 0 << endl;
        return 0;
    }

    long long target = total_sum / 3;
    long long current_sum = 0;
    vector<int> prefix_counts(n, 0);

    // First pass: count the number of times the first part sum equals target up to each index
    for (int i = 0; i < n - 1; ++i) {
        current_sum += a[i];
        if (current_sum == target) {
            prefix_counts[i] = 1;
        }
        // Carry forward the count to the next index
        if (i > 0) {
            prefix_counts[i] += prefix_counts[i - 1];
        }
    }

    current_sum = 0;
    long long result = 0;

    // Second pass: for each index where the suffix sum equals target, add the prefix count up to j-1
    for (int j = n - 1; j >= 1; --j) {
        current_sum += a[j];
        if (current_sum == target && j >= 2) {
            result += prefix_counts[j - 2];
        }
    }

    cout << result << endl;
    return 0;
}