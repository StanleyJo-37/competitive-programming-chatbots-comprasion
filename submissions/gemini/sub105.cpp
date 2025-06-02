#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <algorithm> // Required for std::max function

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // further speeding up I/O. These are common optimizations in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Variable to store the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop through each test case
    while (T--) {
        long long N; // Number of shops. Declared as long long because N can be up to 10^5,
                     // but more importantly, it's compared with max_capacity_time which can be 10^9.
        long long X; // Number of admins. Declared as long long because X can be up to 10^9.
        std::cin >> N >> X; // Read N and X for the current test case

        // Initialize max_capacity_time to 0. This variable will store the maximum
        // time required by any single shop to accommodate all X admins.
        // It must be long long because X can be 10^9 and A_i can be 1,
        // leading to (X + A_i - 1) / A_i being up to 10^9.
        long long max_capacity_time = 0;

        // Loop N times to read the capacity of each shop
        for (int i = 0; i < N; ++i) {
            long long A_i; // Capacity of the i-th shop. Declared as long long because A_i can be up to 10^9.
            std::cin >> A_i; // Read the capacity of the current shop

            // Calculate ceil(X / A_i) using integer division.
            // For positive integers 'a' and 'b', ceil(a/b) can be computed as (a + b - 1) / b.
            // This formula correctly handles cases where 'a' is a multiple of 'b' (e.g., ceil(6/3) = (6+3-1)/3 = 8/3 = 2)
            // and cases where it's not (e.g., ceil(7/3) = (7+3-1)/3 = 9/3 = 3).
            // This 'time_for_this_shop' represents the minimum number of hours required
            // for all X admins to visit this specific shop 'i', given its capacity A_i.
            long long time_for_this_shop = (X + A_i - 1) / A_i;

            // Update max_capacity_time if the current shop requires more time than
            // any previously processed shop. We need to find the maximum among all shops
            // because the total time must be at least as long as the time required by the
            // most restrictive shop.
            max_capacity_time = std::max(max_capacity_time, time_for_this_shop);
        }

        // The minimum total time required is the maximum of two independent lower bounds:
        // 1. N: Each admin must visit N shops, and each visit takes exactly 1 hour.
        //    Therefore, each admin needs at least N hours of shopping time. Since all
        //    admins must complete their shopping, the total time for the entire process
        //    cannot be less than N hours.
        // 2. max_capacity_time: This value represents the maximum time any single shop
        //    needs to process all X admins. Since all X admins must visit every shop,
        //    the total time must be at least this value to satisfy the capacity constraints
        //    of the most bottlenecked shop.
        // The final answer is the maximum of these two values, as both conditions must be met.
        long long result = std::max(N, max_capacity_time);

        // Output the calculated minimum time for the current test case, followed by a newline.
        std::cout << result << std::endl;
    }

    return 0; // Indicate successful execution
}
