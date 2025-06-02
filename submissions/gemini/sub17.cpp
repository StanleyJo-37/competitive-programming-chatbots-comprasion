#include <iostream> // Required for input/output operations (cin, cout).

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the C standard streams and disables synchronization
    // with C's stdio, potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q; // Declare an integer variable 'q' to store the number of queries.
    std::cin >> q; // Read the number of queries from standard input.

    // Loop through each query.
    while (q--) {
        int n; // Declare an integer variable 'n' to store the current number for the query.
        std::cin >> n; // Read the value of 'n' for the current query.

        // To maximize the number of composite summands, we should use the smallest possible composite numbers.
        // The smallest composite number is 4. Other small composite numbers are 6, 8, 9, 10, 12, 14, 15, ...
        // We try to represent 'n' as a sum of as many 4s as possible, and then handle the remainder.

        // Calculate the quotient (number of 4s) and remainder when n is divided by 4.
        int num_fours = n / 4; // 'num_fours' stores the integer division result.
        int remainder = n % 4; // 'remainder' stores the modulo result.

        // Case 1: Remainder is 0 (n is a multiple of 4).
        // Example: n = 12. 12 = 4 + 4 + 4. Number of summands = 3.
        // This is always possible if n >= 4. If n=0, num_fours=0, but n is positive.
        if (remainder == 0) {
            // If n is a multiple of 4, we can represent it as sum of n/4 fours.
            // This gives the maximum number of summands because 4 is the smallest composite.
            std::cout << num_fours << "\n";
        }
        // Case 2: Remainder is 1.
        // Example: n = 9. 9 = 4 + 4 + 1. The '1' is not composite.
        // We need to combine '1' with some 4s to form a composite number.
        // 4 + 1 = 5 (prime)
        // 4 + 4 + 1 = 9 (composite). So we need to use at least two 4s to form a 9.
        // This means we need 'num_fours' to be at least 2.
        // If n = 4k + 1, we need k >= 2.
        // If k >= 2, we can use (k-2) fours and one 9. Total summands: (k-2) + 1 = k-1.
        // For n=9, num_fours=2, remainder=1. num_fours >= 2. Result: 2-1 = 1. (9 itself)
        // For n=13, num_fours=3, remainder=1. num_fours >= 2. Result: 3-1 = 2. (4+9)
        else if (remainder == 1) {
            // If we have at least two 4s (i.e., n >= 8, or num_fours >= 2),
            // we can replace two 4s with a 9 (4+4+1 = 9).
            // This reduces the count of 4s by 2 and adds one 9, so total summands decrease by 1.
            if (num_fours >= 2) {
                std::cout << num_fours - 1 << "\n";
            } else {
                // If num_fours is 0 (n=1) or 1 (n=5), we cannot form a 9.
                // 1, 5 cannot be represented as sum of composite numbers.
                std::cout << -1 << "\n";
            }
        }
        // Case 3: Remainder is 2.
        // Example: n = 6. 6 = 4 + 2. The '2' is not composite.
        // We need to combine '2' with some 4s to form a composite number.
        // 4 + 2 = 6 (composite). So we need to use at least one 4 to form a 6.
        // This means we need 'num_fours' to be at least 1.
        // If n = 4k + 2, we need k >= 1.
        // If k >= 1, we can use (k-1) fours and one 6. Total summands: (k-1) + 1 = k.
        // For n=6, num_fours=1, remainder=2. num_fours >= 1. Result: 1. (6 itself)
        // For n=10, num_fours=2, remainder=2. num_fours >= 1. Result: 2. (4+6)
        else if (remainder == 2) {
            // If we have at least one 4 (i.e., n >= 4, or num_fours >= 1),
            // we can replace one 4 with a 6 (4+2 = 6).
            // This reduces the count of 4s by 1 and adds one 6, so total summands remain the same.
            if (num_fours >= 1) {
                std::cout << num_fours << "\n";
            } else {
                // If num_fours is 0 (n=2), we cannot form a 6.
                // 2 cannot be represented as sum of composite numbers.
                std::cout << -1 << "\n";
            }
        }
        // Case 4: Remainder is 3.
        // Example: n = 15. 15 = 4 + 4 + 4 + 3. The '3' is not composite.
        // We need to combine '3' with some 4s to form a composite number.
        // 4 + 3 = 7 (prime)
        // 4 + 4 + 3 = 11 (prime)
        // 4 + 4 + 4 + 3 = 15 (composite). So we need to use at least three 4s to form a 15.
        // This means we need 'num_fours' to be at least 3.
        // If n = 4k + 3, we need k >= 3.
        // If k >= 3, we can use (k-3) fours and one 15. Total summands: (k-3) + 1 = k-2.
        // For n=15, num_fours=3, remainder=3. num_fours >= 3. Result: 3-2 = 1. (15 itself)
        // For n=19, num_fours=4, remainder=3. num_fours >= 3. Result: 4-2 = 2. (4+15)
        else { // remainder == 3
            // If we have at least three 4s (i.e., n >= 12, or num_fours >= 3),
            // we can replace three 4s with a 15 (4+4+4+3 = 15).
            // This reduces the count of 4s by 3 and adds one 15, so total summands decrease by 2.
            if (num_fours >= 3) {
                std::cout << num_fours - 2 << "\n";
            } else {
                // If num_fours is 0 (n=3), 1 (n=7), or 2 (n=11), we cannot form a 15.
                // 3, 7, 11 cannot be represented as sum of composite numbers.
                std::cout << -1 << "\n";
            }
        }
    }

    return 0; // Indicate successful program execution.
}