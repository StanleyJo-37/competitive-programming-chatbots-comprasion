#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)

// The main function where the program execution begins.
int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // This further optimizes I/O, especially when there's a mix of input and output.
    std::cin.tie(NULL);

    int T; // Declare an integer variable 'T' to store the number of test cases.
    std::cin >> T; // Read the number of test cases from standard input.

    // Loop through each test case. The loop continues as long as T is greater than 0,
    // and T is decremented in each iteration.
    while (T--) {
        int N; // Declare an integer variable 'N' to store the input integer for the current test case.
        std::cin >> N; // Read the integer 'N' from standard input.

        // Problem Analysis:
        // Kulyash needs to break N into a sum of powers of 2.
        // The operation allowed is: choose an integer X and break it into Y + Z.
        // Each operation takes one number (X) and replaces it with two numbers (Y and Z).
        // This means each operation increases the total count of numbers Kulyash possesses by one.

        // Any positive integer N can be uniquely represented as a sum of distinct powers of 2.
        // This is its binary representation. For example:
        // N = 3 (binary 11_2) = 2^1 + 2^0 = 2 + 1. Here, there are 2 distinct powers of 2.
        // N = 7 (binary 111_2) = 2^2 + 2^1 + 2^0 = 4 + 2 + 1. Here, there are 3 distinct powers of 2.
        // N = 4 (binary 100_2) = 2^2 = 4. Here, there is 1 distinct power of 2.

        // Let's say N can be represented as a sum of 'k' distinct powers of 2: N = P1 + P2 + ... + Pk.
        // Initially, Kulyash has 1 number (N).
        // To achieve the goal of having 'k' numbers (P1, P2, ..., Pk), Kulyash needs to perform
        // 'k-1' operations.
        // Example for N=7 (k=3):
        // Start: {7} (1 number)
        // Op 1: Break 7 into 4 + 3. Now Kulyash has {4, 3} (2 numbers).
        // Op 2: Break 3 into 2 + 1. Now Kulyash has {4, 2, 1} (3 numbers).
        // All numbers (4, 2, 1) are powers of 2. Total operations = 2.
        // This matches (k-1) = (3-1) = 2.

        // If N is already a power of 2 (e.g., N=4), its binary representation has only one '1' bit.
        // In this case, k=1. The required operations would be (1-1) = 0. This is correct, as no
        // operations are needed if N is already a power of 2.

        // Therefore, the minimum number of operations is (number of set bits in N) - 1.
        // The number of set bits (or population count) can be efficiently calculated.
        // __builtin_popcount(N) is a GCC/Clang compiler intrinsic that counts the number of set bits
        // in an integer N. It's highly optimized, often mapping directly to a CPU instruction.
        int set_bits_count = __builtin_popcount(N);

        // Output the result for the current test case, followed by a newline.
        std::cout << set_bits_count - 1 << std::endl;
    }

    return 0; // Indicate successful program execution.
}
