#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        // Compute total sum of the array
        int total_sum = 0;
        for (int num : A) {
            total_sum += num;
        }

        int min_sum = INT_MAX;
        int min_index = 0;
        int prefix_sum = 0;

        // Iterate through each index to compute prefixSum(i) + suffixSum(i)
        // suffixSum(i) = total_sum - prefixSum(i-1)
        // So, prefixSum(i) + suffixSum(i) = prefixSum(i) + (total_sum - prefixSum(i-1))
        // But prefixSum(i) = prefixSum(i-1) + A[i-1] (1-based index)
        // Therefore, the expression simplifies to (prefixSum(i-1) + A[i-1] + (total_sum - prefixSum(i-1)) = A[i-1] + total_sum
        // Wait, this suggests that the sum is always A[i-1] + total_sum, which is not matching the sample.
        // Re-evaluating: prefixSum(i) is sum of first i elements (1-based), suffixSum(i) is sum of last N-i+1 elements (1-based)
        // So, suffixSum(i) = sum from A[i-1] to A[N-1] (0-based)
        // Therefore, prefixSum(i) + suffixSum(i) = (A[0] + ... + A[i-1]) + (A[i-1] + ... + A[N-1])
        // Which is total_sum + A[i-1] (since the element A[i-1] is counted twice)
        // So, the minimal value is minimal A[i-1], and the earliest index where A[i-1] is minimal.

        // Thus, the problem reduces to finding the smallest index of the minimal element in the array.
        for (int i = 0; i < N; ++i) {
            int current_sum = A[i] + total_sum;
            if (current_sum < min_sum) {
                min_sum = current_sum;
                min_index = i + 1; // converting to 1-based index
            }
        }

        cout << min_index << endl;
    }
    return 0;
}