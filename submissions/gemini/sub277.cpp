#include <vector> // Required for std::vector

// Function to find the deleted number from a sequence 1 to N.
// The problem states an ordered sequence from 1 to N is given.
// One number might have been deleted, and the remaining numbers were mixed.
// If no number was deleted, the function should return 0.
// N can be 1 or less (e.g., N=0 means the original sequence is empty []).
int findDeletedNumber(const std::vector<int>& mixed_array, int N) {
    // This problem can be efficiently solved using the XOR sum property.
    // The XOR sum of a set of numbers is unique.
    // Property: A ^ B ^ B = A.
    // If we have the XOR sum of the complete sequence (1 to N) and the XOR sum
    // of the mixed array (which is the complete sequence minus one number),
    // then XORing these two sums will yield the missing number.

    // Step 1: Calculate the XOR sum of the complete sequence from 1 to N.
    // Initialize with 0, as XORing any number with 0 does not change its value.
    int xor_sum_original = 0;
    for (int i = 1; i <= N; ++i) {
        xor_sum_original ^= i;
    }

    // Step 2: Calculate the XOR sum of the numbers present in the mixed array.
    int xor_sum_mixed = 0;
    for (int num : mixed_array) {
        xor_sum_mixed ^= num;
    }

    // Step 3: The deleted number is the XOR difference between the two sums.
    // If a number 'X' was deleted, then:
    // xor_sum_original = (XOR sum of all numbers except X) ^ X
    // xor_sum_original = xor_sum_mixed ^ X
    // Therefore, X = xor_sum_original ^ xor_sum_mixed.
    // If no number was deleted, then xor_sum_original will be equal to xor_sum_mixed,
    // and their XOR difference will be 0, which is the required return value for this case.
    return xor_sum_original ^ xor_sum_mixed;

    // Time Complexity: O(N) because we iterate from 1 to N once and iterate through the mixed_array
    // (which has at most N elements) once.
    // Auxiliary Space Complexity: O(1) because we only use a few integer variables for sums.
    // This approach is robust against integer overflow issues that might occur with summation
    // for very large N, as XOR operations do not increase the magnitude of numbers beyond their bit width.
}