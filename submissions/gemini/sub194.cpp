#include <iostream> // Required for input/output operations (cin, cout)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the C standard streams (stdio) and
    // disables synchronization, which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long a; // Declare 'a' as a long long to accommodate values up to 10^18.
    std::cin >> a; // Read the target point 'a' from standard input.

    // Chef's jumps follow a repeating sequence: 1-jump, 2-jump, 3-jump.
    // Let's analyze the points reached:
    // Initial point: 0
    // After 1-jump: 0 + 1 = 1
    // After 2-jump: 1 + 2 = 3
    // After 3-jump: 3 + 3 = 6 (This completes one cycle of 3 jumps)
    //
    // The total distance covered in one full cycle (1-jump, 2-jump, 3-jump) is 1 + 2 + 3 = 6.
    //
    // Let's list the reachable points and their pattern:
    // Points after k full cycles (0, 1, 2, ...):
    // k=0: 0
    // k=1: 6 (after 1 full cycle)
    // k=2: 12 (after 2 full cycles)
    // In general, points of the form 6k are reachable.
    //
    // Points after k full cycles and one 1-jump:
    // From 6k, jump +1: 6k + 1
    // Examples: 1 (from 0), 7 (from 6), 13 (from 12)
    //
    // Points after k full cycles, one 1-jump, and one 2-jump:
    // From 6k + 1, jump +2: 6k + 1 + 2 = 6k + 3
    // Examples: 3 (from 1), 9 (from 7), 15 (from 13)
    //
    // Points after k full cycles, one 1-jump, one 2-jump, and one 3-jump:
    // From 6k + 3, jump +3: 6k + 3 + 3 = 6k + 6 = 6(k+1)
    // This brings us to the start of the next cycle, which is already covered by 6k.
    //
    // Therefore, a point 'a' is reachable if it can be expressed in one of these forms:
    // 1. a = 6k (meaning a % 6 == 0)
    // 2. a = 6k + 1 (meaning a % 6 == 1)
    // 3. a = 6k + 3 (meaning a % 6 == 3)
    //
    // Any other remainder when 'a' is divided by 6 (i.e., 2, 4, or 5) means the point is not reachable.

    long long remainder = a % 6; // Calculate the remainder when 'a' is divided by 6.

    // Check if the remainder is one of the allowed values (0, 1, or 3).
    if (remainder == 0 || remainder == 1 || remainder == 3) {
        std::cout << "yes\n"; // If 'a' is reachable, print "yes" followed by a newline.
    } else {
        std::cout << "no\n"; // Otherwise, print "no" followed by a newline.
    }

    return 0; // Indicate successful program execution.
}
