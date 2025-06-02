#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Calculate total sum of the array
    long long total_sum = 0;
    for (int i = 0; i < n; ++i) total_sum += a[i];

    // If total sum is not divisible by 3, it's impossible to split
    if (total_sum % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    long long part_sum = total_sum / 3;

    // We will use prefix sums to count the number of ways
    // First, we traverse from right to left to count, for each position,
    // how many suffixes (ending at or after that position) have sum == part_sum
    vector<int> suffix_count(n, 0);
    long long suffix_sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        suffix_sum += a[i];
        if (suffix_sum == part_sum) {
            suffix_count[i] = 1;
        }
    }
    // Now, accumulate the counts so that suffix_count[i] is the number of suffixes
    // starting at i or after with sum == part_sum
    for (int i = n - 2; i >= 0; --i) {
        suffix_count[i] += suffix_count[i + 1];
    }

    // Now, traverse from left to right, for each possible split point i (i from 0 to n-3),
    // if prefix sum == part_sum, add the number of suffixes starting at i+2 (i.e., j+1 >= i+2)
    long long prefix_sum = 0;
    long long ways = 0;
    for (int i = 0; i <= n - 3; ++i) {
        prefix_sum += a[i];
        if (prefix_sum == part_sum) {
            // The middle part must be at least one element, so j >= i+1
            // The third part must be at least one element, so j <= n-2
            // So, we count suffix_count[i+2] (i+2 <= n-1)
            ways += suffix_count[i + 2];
        }
    }

    cout << ways << '\n';
    return 0;
}