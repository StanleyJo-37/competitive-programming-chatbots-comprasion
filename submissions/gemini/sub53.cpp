#include <vector> // Required for std::vector

// Function to calculate a custom Fibonacci-like sequence element.
// signature: The initial sequence elements. Its length determines the 'window' size for summing.
// indexes: A list of 0-based indices relative to the last 'length' elements to sum.
//          For example, if length is 5 and indexes is [1,4,2], it means sum the 2nd, 5th, and 3rd
//          elements (at relative indices 1, 4, and 2) of the last 5 numbers.
// n: The 0-based index of the sequence element to return.
long long custom_fib(const std::vector<long long>& signature, const std::vector<int>& indexes, int n) {
    // Get the length of the signature. This value defines the size of the sliding window
    // of previous elements used to calculate the next number in the sequence.
    int length = signature.size();

    // Handle base cases: If 'n' is less than the 'length' of the signature,
    // the requested element is already present in the initial 'signature' list.
    // This avoids unnecessary calculations and array out-of-bounds access for small 'n'.
    if (n < length) {
        return signature[n];
    }

    // Create a mutable vector to store the sequence elements as they are generated.
    // Initialize it with the provided 'signature' elements.
    std::vector<long long> sequence = signature;

    // Iterate from 'length' (the first index to be calculated) up to 'n' (the target index).
    // In each iteration, 'i' represents the index of the element currently being calculated.
    for (int i = length; i <= n; ++i) {
        long long next_element_sum = 0; // Initialize the sum for the new element.

        // Calculate the next element by summing values from the 'window' of previous elements.
        // The 'window' consists of the last 'length' elements in the 'sequence' vector.
        // For an element at index 'i', these 'length' elements range from 'sequence[i - length]'
        // up to 'sequence[i - 1]'.
        // Each 'idx' in the 'indexes' vector specifies an offset within this window.
        // So, 'sequence[i - length + idx]' correctly accesses the element at the relative position 'idx'.
        for (int idx : indexes) {
            // Add the value of the element at the calculated position to the sum.
            // 'i - length' gives the starting index of the current window in the 'sequence' vector.
            // Adding 'idx' to it gives the absolute index of the specific element within that window.
            next_element_sum += sequence[i - length + idx];
        }
        // After summing all required elements, append the calculated 'next_element_sum'
        // to the end of the 'sequence' vector.
        sequence.push_back(next_element_sum);
    }

    // Once the loop completes, the 'sequence' vector will contain all elements
    // from index 0 up to the requested index 'n'.
    // Return the element at the target index 'n'.
    return sequence[n];
}