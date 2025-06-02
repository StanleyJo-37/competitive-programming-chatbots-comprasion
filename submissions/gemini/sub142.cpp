#include <iostream> // Required for input/output operations (cin, cout)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the C standard streams and disables synchronization
    // with C's stdio, which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare an integer variable T for the number of test cases.
    std::cin >> T; // Read the number of test cases.

    // Loop through each test case.
    while (T--) {
        long long N; // Declare a long long variable N for the number of elements.
                     // N can be up to 10^9, which fits in a 32-bit signed int,
                     // but using long long is safer and common practice for large inputs.
        int A;       // Declare an int variable A for the bitwise AND value.
                     // A can be up to 10^9, which fits in a 32-bit signed int.
        std::cin >> N >> A; // Read N and A for the current test case.

        // Determine the parity of A (its least significant bit).
        // If A is odd, A & 1 will be 1. If A is even, A & 1 will be 0.
        bool a_is_odd = (A % 2 != 0); // Or (A & 1) == 1;

        if (a_is_odd) {
            // Case 1: A is Odd.
            // If the bitwise AND of all elements (A) is Odd, it means the least significant bit (LSB)
            // of A is 1. For the LSB of the bitwise AND to be 1, the LSB of *every* element
            // in the array must be 1. This implies that every element x_i in the array must be Odd.
            //
            // The sum of N Odd numbers:
            // - If N is Odd (e.g., Odd + Odd + Odd), the sum is Odd.
            // - If N is Even (e.g., Odd + Odd), the sum is Even.
            //
            // So, the parity of the sum is the same as the parity of N.
            if (N % 2 != 0) {
                std::cout << "Odd\n"; // N is Odd, sum is Odd.
            } else {
                std::cout << "Even\n"; // N is Even, sum is Even.
            }
        } else {
            // Case 2: A is Even.
            // If the bitwise AND of all elements (A) is Even, it means the LSB of A is 0.
            // For the LSB of the bitwise AND to be 0, it means that *at least one* element
            // in the array must have its LSB as 0. This implies that at least one element x_j
            // in the array must be Even.
            //
            // We need to determine if the sum's parity is uniquely determined or if it can vary.

            if (N == 1) {
                // Subcase 2.1: N = 1.
                // If there's only one element, that element must be A itself.
                // So, x_1 = A.
                // Since A is Even (as per this 'else' block), x_1 is Even.
                // The sum is x_1, which is Even.
                // The parity is uniquely determined as Even.
                std::cout << "Even\n";
            } else {
                // Subcase 2.2: N > 1.
                // We know at least one element must be Even.
                //
                // Possibility 1: Construct an array that results in an Even sum.
                // We can set all elements x_i = A.
                // The bitwise AND of [A, A, ..., A] is A. This is a valid array.
                // Since A is Even, all elements are Even.
                // The sum (N * A) of N Even numbers is always Even.
                // So, an Even sum is possible.
                //
                // Possibility 2: Construct an array that results in an Odd sum.
                // We need an Odd number of Odd elements. Since at least one element must be Even,
                // we cannot make all N elements Odd. The maximum number of Odd elements is N-1.
                // Let's try to make exactly one element Odd and N-1 elements Even.
                // Let x_1 = A | 1. (Since A is Even, A|1 will have its LSB as 1, making x_1 Odd).
                // For i = 2 to N, let x_i = A. (These elements are Even, as A is Even).
                //
                // Check the bitwise AND of this constructed array:
                // (A | 1) & A & A & ... & A = (A | 1) & A.
                // For any bit position k:
                // - If the k-th bit of A is 1, then (A|1)_k is 1, and A_k is 1. So (A|1)_k & A_k = 1.
                // - If the k-th bit of A is 0, then (A|1)_k can be 0 or 1 (depending on whether k=0 or k>0).
                //   However, A_k is 0. So (A|1)_k & A_k = 0.
                // Thus, (A | 1) & A = A. This construction is valid.
                //
                // In this construction, we have one Odd element (x_1 = A|1) and N-1 Even elements (x_i = A).
                // The sum of one Odd number and N-1 Even numbers is Odd.
                // So, an Odd sum is possible.
                //
                // Since both Even and Odd sums are possible, the parity cannot be determined.
                std::cout << "Impossible\n";
            }
        }
    }

    return 0; // Indicate successful execution.
}
