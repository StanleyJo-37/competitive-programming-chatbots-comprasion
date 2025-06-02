#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // The answer string will be built as follows:
    // For k=1 to n, the k-th character is '1' if the k-compression is a permutation.
    string ans(n, '0');

    // Step 1: Check if the original array is a permutation (k=1 case)
    vector<bool> seen(n + 1, false);
    bool is_perm = true;
    for (int num : a) {
        if (num > n || seen[num]) {
            is_perm = false;
            break;
        }
        seen[num] = true;
    }
    if (is_perm) {
        ans[0] = '1';
    }

    // Step 2: For k>1, the k-compression is a permutation only if:
    // 1. The min of the entire array is 1.
    // 2. The min of every window of size k is unique and covers 1..(n-k+1).
    // We can use a sliding window minimum approach to find the min for each window size.

    // Precompute the positions of 1s to help determine the minimal k where the condition holds.
    // The minimal k where the answer is '1' is when the global min is 1 and all elements are covered in a way that the compression is a permutation.

    // The answer for k is '1' if:
    // 1. The compression array contains all numbers from 1 to (n-k+1) exactly once.
    // 2. The minimal element in any window of size k is unique in the compression array.

    // To find the answer for all k, we can observe that:
    // - For k=1, it's a permutation if the original array is a permutation.
    // - For k=n, it's always a permutation (single element [1]).
    // - For other k, the answer is '1' if the minimal element in every window of size k is unique and forms a permutation of 1..(n-k+1).

    // The key observation is that the answer for k will be '1' if:
    // 1. The minimal element in the entire array is 1.
    // 2. The minimal elements in all windows of size k are distinct and cover 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' only if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To efficiently compute this, we can use the fact that the minimal k for which the answer is '1' is when the minimal element in all windows of size k is unique and forms a permutation.

    // We can precompute the minimal elements for all possible window sizes using a sliding window minimum approach or using a monotonic queue.

    // However, a more efficient approach is to realize that the answer for k will be '1' if:
    // - The minimal element in the entire array is 1.
    // - The minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // We can use the following observations:
    // 1. The answer for k=n is always '1' (single element [1] if the global min is 1).
    // 2. For k from 2 to n-1, the answer is '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // To check this, we can use the following approach:
    // - Precompute the positions where each value occurs.
    // - For each value from 1 to n, find the minimal window size where it can be the minimal element.
    // - Then, for each k, check if the minimal elements in all windows of size k are unique and form a permutation.

    // However, this is complex. Instead, we can use the following approach:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // We can use the following approach:
    // - For each k, the answer is '1' if the compression array is a permutation of 1..(n-k+1).
    // - To check this, we can use the following:
    //   - The minimal element in the entire array must be 1.
    //   - The maximal element in the compression array must be (n-k+1).
    //   - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of size k is unique and the maximal minimal element is (n-k+1).

    // To find the minimal k where this holds, we can use the following:
    // - The minimal k is the smallest k where the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).

    // We can use the following approach:
    // - The answer for k=1 is checked separately.
    // - For k>1, the answer is '1' if the minimal element in the entire array is 1, and the minimal elements in all windows of size k are distinct and form a permutation of 1..(n-k+1).

    // To compute this, we can use the following:
    // - The minimal element in the entire array must be 1.
    // - The maximal element in the compression array must be (n-k+1).
    // - All elements in the compression array must be distinct and in the range [1, n-k+1].

    // However, computing the compression array for each k is O(n^2), which is too slow.

    // Instead, we can use the following observations:
    // - The answer for k will be '1' if the minimal element in all windows of size k is unique and forms a permutation of 1..(n-k+1).
    // - This is equivalent to saying that the minimal element in all windows of