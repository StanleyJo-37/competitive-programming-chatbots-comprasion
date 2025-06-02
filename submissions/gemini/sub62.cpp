#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // Not strictly necessary, manual multiplication for powers of 3 is used.

// Function to solve a single query
void solve() {
    long long n;
    std::cin >> n;

    // Step 1: Convert n to its ternary (base-3) representation.
    // Store digits in a vector, where digits[i] is the coefficient of 3^i.
    // Example: n=19. 19 = 2*3^2 + 0*3^1 + 1*3^0. So digits = {1, 0, 2}.
    std::vector<int> digits;
    long long temp_n = n;
    // The problem states n is a positive integer, so n >= 1.
    // Thus, temp_n will always be > 0 initially.
    while (temp_n > 0) {
        digits.push_back(temp_n % 3);
        temp_n /= 3;
    }

    // Step 2: Find the highest index (most significant digit) that is '2'.
    // A "good" number has only '0's and '1's in its ternary representation.
    // If a '2' exists, n is not good. We need to find the smallest m >= n that is good.
    int first_two_idx = -1;
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] == 2) {
            first_two_idx = i;
            break; // Found the most significant '2', no need to check further left.
        }
    }

    // Step 3: If no '2' is found, n is already a good number.
    // In this case, n itself is the smallest good number greater than or equal to n.
    if (first_two_idx == -1) {
        std::cout << n << std::endl;
        return;
    }

    // Step 4: If a '2' is found at first_two_idx, we need to modify n to find m.
    // To find the smallest m >= n that is good, we must "fix" this '2'.
    // We cannot have a '2' at first_two_idx. If we change it to '0' or '1' without
    // affecting higher-order digits, the resulting number would be smaller than n.
    // Therefore, we must increment a digit at some position 'p' such that p >= first_two_idx.
    // To make 'm' the smallest possible, we want to increment the digit at the smallest
    // possible index 'p' (from first_two_idx upwards) such that digits[p] becomes '1'
    // and all digits to its right (indices < p) become '0'.
    // This means we need to find the first '0' digit at or to the left of first_two_idx.
    // (i.e., smallest index 'p' such that p >= first_two_idx and digits[p] == 0).
    int fix_pos = -1;
    for (int i = first_two_idx; i < digits.size(); ++i) {
        if (digits[i] == 0) {
            fix_pos = i;
            break; // Found the lowest index '0' at or above first_two_idx.
        }
    }

    // Case A: No '0' is found from first_two_idx up to the most significant digit.
    // This implies that all digits from first_two_idx to digits.size()-1 are '1's or '2's.
    // Since first_two_idx is the *highest* index with a '2', all digits at indices
    // greater than first_two_idx must be '1's.
    // So, the ternary representation of n effectively looks like (1...12...).
    // In this scenario, we cannot simply increment an existing digit to '1' without
    // creating another '2' or making the number smaller.
    // The smallest good number m will require an additional most significant digit.
    // This means m will be 3^(current_number_of_digits).
    // Example: n=14=(112)_3. first_two_idx=0. No '0' found. Result is 3^3 = 27.
    if (fix_pos == -1) {
        long long m = 1;
        // Calculate 3^(digits.size())
        for (int i = 0; i < digits.size(); ++i) {
            m *= 3;
        }
        std::cout << m << std::endl;
    }
    // Case B: A '0' is found at fix_pos.
    // We can increment digits[fix_pos] to '1'.
    // To ensure 'm' is the smallest good number >= n, all digits at indices
    // less than fix_pos must be set to '0'.
    // Digits at indices greater than fix_pos remain unchanged, as we found the
    // leftmost possible position to increment, preserving the most significant prefix.
    else {
        digits[fix_pos] = 1;
        for (int i = 0; i < fix_pos; ++i) {
            digits[i] = 0;
        }

        // Step 5: Convert the modified ternary digits back to a decimal number.
        long long m = 0;
        long long power_of_3 = 1; // Represents 3^0, 3^1, 3^2, ...
        for (int i = 0; i < digits.size(); ++i) {
            m += digits[i] * power_of_3;
            power_of_3 *= 3;
        }
        std::cout << m << std::endl;
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and disables synchronization with C stdio.
    // It can significantly speed up I/O operations, which is crucial for problems
    // with large inputs or many queries.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q;
    std::cin >> q; // Read the number of queries
    while (q--) {
        solve(); // Solve each independent query
    }

    return 0;
}
