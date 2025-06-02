#include <vector> // Required for std::vector

// Function to find an index N where the sum of integers to the left of N
// is equal to the sum of integers to the right of N.
// If multiple such indices exist, the lowest one is returned.
// If no such index is found, -1 is returned.
// Empty arrays are considered to have a sum of 0.
int findEvenIndex(const std::vector<int>& arr) {
    // The problem statement guarantees array length 0 < arr < 1000,
    // so arr will not be empty. However, an empty check is generally good practice.
    // if (arr.empty()) {
    //     return -1; // An empty array has no valid index.
    // }

    // Calculate the total sum of all elements in the array.
    // Using 'long long' for sums to prevent potential integer overflow.
    // Array elements can be positive or negative, and with up to 999 elements,
    // their sum might exceed the range of a standard 'int'.
    long long total_sum = 0;
    for (int x : arr) {
        total_sum += x;
    }

    // Initialize 'left_sum' to 0. This represents the sum of elements
    // to the left of the current index N. For N=0, the left side is empty, so its sum is 0.
    long long left_sum = 0;

    // Iterate through each possible index N from 0 to arr.size() - 1.
    // We are looking for the lowest index, so iterating from left to right
    // and returning the first match ensures this.
    for (int N = 0; N < arr.size(); ++N) {
        // Calculate 'right_sum'. The total sum of the array can be expressed as:
        // total_sum = (sum of elements to the left of N) + arr[N] + (sum of elements to the right of N)
        // So, right_sum = total_sum - left_sum - arr[N].
        long long right_sum = total_sum - left_sum - arr[N];

        // Check if the sum of the left side equals the sum of the right side.
        if (left_sum == right_sum) {
            // If they are equal, N is an equilibrium index.
            // Since we iterate from N=0 upwards, this is the lowest such index.
            return N;
        }

        // For the next iteration (N+1), the current element arr[N] will be
        // part of the left sum. So, update 'left_sum' by adding arr[N].
        left_sum += arr[N];
    }

    // If the loop completes without finding any equilibrium index,
    // it means no such index exists. Return -1 as per the problem requirements.
    return -1;
}
