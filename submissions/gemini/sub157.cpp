#include <iostream>
#include <vector>
#include <algorithm> // For std::upper_bound

// Global vector to store precomputed good numbers.
// A good number is one whose binary representation is palindromic.
std::vector<int> good_numbers;

/**
 * @brief Checks if the binary representation of a non-negative integer is palindromic.
 * @param n The integer to check.
 * @return true if the binary representation is palindromic, false otherwise.
 *
 * This function determines the number of bits in 'n' and then compares bits
 * from the most significant end with corresponding bits from the least significant end.
 */
bool is_palindrome_binary(int n) {
    // According to problem constraints, n >= 1.
    // If n could be 0, its binary "0" is palindromic.
    if (n == 0) return true; 

    int num_bits = 0;
    int temp_n = n;
    // Count the number of bits required to represent n.
    while (temp_n > 0) {
        temp_n >>= 1; // Right shift to check next bit
        num_bits++;   // Increment bit count
    }

    // Compare bits from both ends towards the center.
    // We only need to iterate up to half the number of bits.
    for (int i = 0; i < num_bits / 2; ++i) {
        // Get the i-th bit from the least significant end (0-indexed).
        int right_bit = (n >> i) & 1;
        // Get the i-th bit from the most significant end (0-indexed from MSB).
        // This is equivalent to the (num_bits - 1 - i)-th bit from the LSB end.
        int left_bit = (n >> (num_bits - 1 - i)) & 1;

        // If any pair of corresponding bits do not match, it's not a palindrome.
        if (left_bit != right_bit) {
            return false;
        }
    }
    return true; // All checked bits matched, so it's a palindrome.
}

/**
 * @brief Precomputes and stores all "good" numbers up to 1000.
 *
 * This function iterates through numbers from 1 to 1000. For each number,
 * it checks if its binary representation is palindromic using `is_palindrome_binary`.
 * If it is, the number is added to the global `good_numbers` vector.
 * The vector will be sorted in ascending order.
 */
void precompute_good_numbers() {
    for (int i = 1; i <= 1000; ++i) {
        if (is_palindrome_binary(i)) {
            good_numbers.push_back(i);
        }
    }
}

/**
 * @brief Solves a single test case.
 *
 * Reads an integer 'n' and expresses it as a sum of at most 12 good numbers.
 * It uses a greedy approach: repeatedly subtracts the largest good number
 * less than or equal to the current remaining sum until the sum becomes 0.
 * This greedy strategy is efficient and guaranteed to find a solution within
 * the given constraints (at most 4 terms for N <= 1000).
 */
void solve() {
    int n;
    std::cin >> n; // Read the input number n

    std::vector<int> result_numbers; // Stores the good numbers found for the sum

    // Continue until n becomes 0.
    while (n > 0) {
        // Find the largest good number 'g' such that 'g <= n'.
        // std::upper_bound returns an iterator to the first element in `good_numbers`
        // that is strictly greater than 'n'.
        auto it = std::upper_bound(good_numbers.begin(), good_numbers.end(), n);
        
        // Since n >= 1 and 1 is always a good number, `it` will never be `good_numbers.begin()`.
        // Decrementing `it` gives an iterator to the largest good number less than or equal to 'n'.
        --it; 
        int best_good_num = *it;

        result_numbers.push_back(best_good_num); // Add this good number to our result.
        n -= best_good_num; // Reduce n by the chosen good number.
    }

    // Print the count of good numbers used.
    std::cout << result_numbers.size() << std::endl;
    // Print the sequence of good numbers.
    for (size_t i = 0; i < result_numbers.size(); ++i) {
        std::cout << result_numbers[i] << (i == result_numbers.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

/**
 * @brief Main function to handle test cases.
 *
 * Sets up fast I/O, calls `precompute_good_numbers` once,
 * then processes each test case by calling `solve()`.
 */
int main() {
    // Optimize C++ standard streams for faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Precompute all necessary good numbers once before processing any test cases.
    precompute_good_numbers();

    int t;
    std::cin >> t; // Read the total number of test cases.
    while (t--) {  // Loop through each test case.
        solve();   // Solve the current test case.
    }

    return 0;
}
