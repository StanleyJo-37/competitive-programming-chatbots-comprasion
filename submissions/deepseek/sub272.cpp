#include <vector>
#include <numeric> // For std::accumulate

int find_even_index(const std::vector<int> &arr) {
    // Iterate through each index in the array
    for (size_t i = 0; i < arr.size(); ++i) {
        // Calculate left sum (from start to i-1)
        int left_sum = 0;
        for (size_t j = 0; j < i; ++j) {
            left_sum += arr[j];
        }
        
        // Calculate right sum (from i+1 to end)
        int right_sum = 0;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            right_sum += arr[j];
        }
        
        // Check if sums are equal
        if (left_sum == right_sum) {
            return i; // Return the first valid index found
        }
    }
    
    return -1; // No valid index found
}