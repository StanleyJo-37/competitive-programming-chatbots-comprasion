#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <numeric>  // Required for std::gcd (C++17 for standard GCD function)

// Function to solve a single test case
void solve() {
    long long n; // Declare n as long long to handle values up to 10^9
    std::cin >> n; // Read the input integer n

    // Case 1: n is an even number.
    // We choose c = 1.
    // Then a + b + 1 = n, which means a + b = n - 1.
    // We need gcd(a, b) = 1.
    // Let's pick a = 2.
    // Then b = (n - 1) - 2 = n - 3.
    // Check conditions for a=2, b=n-3, c=1:
    // 1. a, b, c are positive:
    //    a = 2 (positive).
    //    c = 1 (positive).
    //    b = n - 3. Since n >= 10, n - 3 >= 7, so b is positive.
    // 2. a, b, c are distinct:
    //    a = 2 is distinct from c = 1.
    //    b = n - 3. Since n >= 10, n - 3 >= 7, so b is distinct from 1 and 2.
    //    All three are distinct.
    // 3. a + b + c = n:
    //    2 + (n - 3) + 1 = n. This sum is correct.
    // 4. gcd(a, b) = c:
    //    gcd(2, n - 3). Since n is even, n - 3 is odd.
    //    The greatest common divisor of an even number (2) and an odd number (n-3) is always 1.
    //    So, gcd(2, n - 3) = 1, which is equal to c. This condition is satisfied.
    // This construction works for all even n >= 10.
    if (n % 2 == 0) {
        std::cout << 2 << " " << n - 3 << " " << 1 << std::endl;
    } else {
        // Case 2: n is an odd number.
        // We try to choose c = 1.
        // Then a + b + 1 = n, which means a + b = n - 1.
        // We need gcd(a, b) = 1.
        // Since n is odd, n - 1 is even.
        // For gcd(a, b) = 1, a and b must be coprime.
        // If a and b had different parities, their sum (a+b) would be odd. But n-1 is even.
        // So, a and b must have the same parity.
        // If a and b were both even, then gcd(a, b) would be at least 2, which is not 1 (our chosen c).
        // Therefore, a and b must both be odd.
        // We need to find two distinct odd positive integers a, b, both > 1, such that gcd(a, b) = 1 and a + b = n - 1.

        // We iterate through small odd integers for 'a' (which corresponds to k_1).
        // We start with a_val = 3 because 'a' must be odd and greater than 1.
        // This loop is guaranteed to find a solution quickly because n-1 cannot be divisible by all small primes.
        // The problem statement guarantees that an answer always exists.
        for (long long a_val = 3; ; a_val += 2) { // a_val will take values 3, 5, 7, ...
            long long b_val = n - 1 - a_val; // Calculate b_val such that a_val + b_val = n - 1

            // Check if a_val and b_val are coprime.
            // The property gcd(x, y) = gcd(x, y-x) implies gcd(a_val, b_val) = gcd(a_val, (n-1-a_val)) = gcd(a_val, n-1).
            // So we need gcd(a_val, n-1) to be 1.
            if (std::gcd(a_val, b_val) == 1) {
                // All conditions for a_val, b_val, c=1 are met:
                // 1. a_val, b_val, c=1 are positive:
                //    a_val >= 3 (positive). c=1 (positive).
                //    b_val = n - 1 - a_val. Since n >= 10 and a_val is small (e.g., max 29),
                //    n - 1 - a_val will always be > 1 (e.g., 10-1-29 is negative, but a_val won't reach 29 for n=10.
                //    For n=10, it's even case. For n=11, a_val=3, b_val=7. For n=31, a_val=7, b_val=23.
                //    The smallest n for which b_val <= 1 for a_val=3 is n=5, but n>=10. So b_val is always positive.
                // 2. a_val, b_val, c=1 are distinct:
                //    a_val >= 3 is distinct from c=1.
                //    b_val = n - 1 - a_val. Since n >= 10 and a_val is small, b_val will be >= 4.
                //    So b_val is distinct from 1.
                //    b_val is distinct from a_val (i.e., a_val != n-1-a_val => 2*a_val != n-1).
                //    For example, if a_val=3, 2*3=6. n-1=6 implies n=7. But n>=10.
                //    If a_val=5, 2*5=10. n-1=10 implies n=11. For n=11, a_val=3 is tried first (b_val=7, gcd(3,7)=1), so (3,7,1) is printed.
                //    Thus, a_val and b_val will always be distinct.
                // 3. a_val + b_val + c = n:
                //    a_val + (n - 1 - a_val) + 1 = n. This is correct.
                // 4. gcd(a_val, b_val) = c:
                //    We explicitly checked this condition in the if statement.

                std::cout << a_val << " " << b_val << " " << 1 << std::endl;
                break; // Found a solution, exit the loop
            }
        }
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // which can also speed up I/O.
    std::cin.tie(NULL);

    int t; // Declare t for the number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop t times, decrementing t each iteration
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}
