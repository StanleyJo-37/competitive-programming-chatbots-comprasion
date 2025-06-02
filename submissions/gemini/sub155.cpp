#include <iostream> // Required for input/output operations
#include <vector>   // Not strictly needed for this problem, but often useful

// Function to solve a single test case
void solve() {
    int n; // The upper bound for the password (password is between 0 and n-1)
    int k; // The base for k-itwise XOR (always 2 in this version)
    std::cin >> n >> k; // Read n and k

    int current_xor_sum = 0; // This variable will store the XOR sum of all previous guesses.
                             // Let P_0 be the initial password.
                             // After i queries G_0, G_1, ..., G_{i-1},
                             // the current password P_i is P_0 XOR (G_0 XOR ... XOR G_{i-1}).
                             // So, P_i = P_0 XOR current_xor_sum.

    for (int i = 0; i < n; ++i) { // We can make at most n queries.
                                  // We iterate through possible initial passwords from 0 to n-1.
                                  // If the initial password P_0 is 'i', then at this step 'i',
                                  // our guess will be correct.
        
        // Our strategy is to guess a value 'y' such that if 'y' is the current password P_i,
        // then it implies that the initial password P_0 was 'i'.
        // We know P_i = P_0 XOR current_xor_sum.
        // If we guess 'y' and it's correct, then y = P_i.
        // So, y = P_0 XOR current_xor_sum.
        // We want this to imply P_0 = i.
        // Thus, we need y = i XOR current_xor_sum.
        int guess = i ^ current_xor_sum; 

        std::cout << guess << std::endl; // Print our guess
        std::cout.flush(); // Flush the output buffer to ensure the query is sent

        int response; // Variable to store the system's response
        std::cin >> response; // Read the response

        if (response == 1) {
            // If response is 1, our guess was correct.
            // This means 'guess' was equal to the current password P_i.
            // From our strategy, guess = i ^ current_xor_sum.
            // And we know P_i = P_0 ^ current_xor_sum.
            // So, i ^ current_xor_sum = P_0 ^ current_xor_sum.
            // This implies i = P_0. We have found the initial password.
            break; // Exit the loop and move to the next test case
        } else if (response == 0) {
            // If response is 0, our guess was incorrect.
            // The password changes from P_i to P_{i+1} such that P_i XOR P_{i+1} = guess.
            // This means P_{i+1} = P_i XOR guess.
            // We need to update current_xor_sum for the next iteration.
            // The new current_xor_sum (for P_{i+1}) should be current_xor_sum_old XOR guess.
            current_xor_sum ^= guess; 
            // Let's verify the invariant:
            // P_{i+1} = P_i XOR guess
            // P_{i+1} = (P_0 XOR current_xor_sum_old) XOR guess
            // P_{i+1} = P_0 XOR (current_xor_sum_old XOR guess)
            // P_{i+1} = P_0 XOR current_xor_sum_new.
            // The invariant holds.
        } else {
            // If response is -1, it means an invalid query or exceeded query limit.
            // As per problem statement, we must exit immediately.
            return; 
        }
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop through each test case
        solve(); // Solve the current test case
    }

    return 0; // Indicate successful execution
}
