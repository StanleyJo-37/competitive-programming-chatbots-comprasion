#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation
#include <numeric>  // Not strictly needed, but often useful for algorithms like std::accumulate
#include <algorithm> // Not strictly needed, but often useful for algorithms like std::count

void solve() {
    // N: length of the binary string S
    int N;
    std::cin >> N;
    // S: the binary string
    std::string S;
    std::cin >> S;

    // count0: stores the number of '0's in S
    int count0 = 0;
    // count1: stores the number of '1's in S
    int count1 = 0;

    // Iterate through the string to count '0's and '1's
    for (char c : S) {
        if (c == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    // A binary string S is a xor palindrome if S_i XOR S_(N+1-i) is the same for all 1 <= i <= N.
    // Let this constant XOR value be C. C can be 0 or 1.

    // Case 1: C = 0
    // If S_i XOR S_(N+1-i) = 0, it implies S_i = S_(N+1-i).
    // This means the string must be a regular palindrome.
    // For a string to be rearrangeable into a regular palindrome:
    // - If N is even: All characters must appear an even number of times.
    //   (i.e., count0 must be even, and count1 must be even).
    //   Since count0 + count1 = N (which is even), if count0 is even, count1 must also be even.
    //   So, this condition simplifies to count0 % 2 == 0.
    // - If N is odd: At most one character can appear an odd number of times.
    //   (Since count0 + count1 = N (which is odd), one count must be odd and the other even. This condition is always met).
    //   Thus, for odd N, it's always possible to form a regular palindrome with the given counts.
    //   (e.g., the character with the odd count can be placed in the middle, and others form pairs).

    // Case 2: C = 1
    // If S_i XOR S_(N+1-i) = 1, it implies S_i != S_(N+1-i).
    // This means for each pair of characters (S_i, S_(N+1-i)), one must be '0' and the other '1'.
    // - If N is odd: This case is impossible. The middle character S_((N+1)/2) would be paired with itself.
    //   S_m XOR S_m = 0, but we require S_m XOR S_m = 1, which is a contradiction.
    // - If N is even: There are N/2 such pairs. Each pair must consist of one '0' and one '1'.
    //   This means we need exactly N/2 '0's and N/2 '1's.
    //   (i.e., count0 == N/2 and count1 == N/2).
    //   Since count0 + count1 = N, if count0 == N/2, then count1 must also be N/2.
    //   So, this condition simplifies to count0 == N/2.

    // Combining the conditions for possibility:
    // If N is odd:
    //   As explained above, only C=0 is possible, and it's always achievable for any valid counts.
    //   Therefore, if N is odd, the answer is always YES.
    if (N % 2 != 0) {
        std::cout << "YES\n";
    }
    // If N is even:
    //   We need to check if either a C=0 xor palindrome OR a C=1 xor palindrome is possible.
    //   Possibility for C=0: count0 must be even.
    //   Possibility for C=1: count0 must be N/2.
    //   If either of these conditions is met, it's possible to rearrange S into a xor palindrome.
    else { // N is even
        if (count0 % 2 == 0 || count0 == N / 2) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // T: number of test cases
    int T;
    std::cin >> T;
    // Loop through each test case
    while (T--) {
        solve();
    }

    return 0; // Indicate successful execution
}
