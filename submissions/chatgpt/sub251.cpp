#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) cin >> A[i];

        // Sort the array to make median calculation and subsequence selection easier
        sort(A.begin(), A.end());

        // Initialize minimum beauty to a large value
        long long min_beauty = LLONG_MAX;

        // For every triplet of consecutive elements in the sorted array,
        // calculate the beauty and keep the minimum.
        // This works because for any sorted triplet (a, b, c), the median is b,
        // and the mean is (a+b+c)/3. The minimum beauty is always achieved
        // for consecutive elements in the sorted array.
        for (int i = 0; i + 2 < N; ++i) {
            long long a = A[i];
            long long b = A[i+1];
            long long c = A[i+2];

            // The mean of the triplet
            long long sum = a + b + c;
            // The median is always b (since the array is sorted)
            long long median = b;

            // The mean can be a non-integer, but the beauty is always integer
            // because 3 * abs(mean - median) = abs(sum - 3*median)
            long long beauty = abs(sum - 3 * median);

            if (beauty < min_beauty) min_beauty = beauty;
        }

        // Output the minimum beauty for this test case
        cout << min_beauty << '\n';
    }
    return 0;
}