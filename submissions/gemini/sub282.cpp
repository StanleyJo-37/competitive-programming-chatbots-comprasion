#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector, which is a dynamic array

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // leading to faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N; // Declare an integer variable N to store the number of balloons.
    std::cin >> N; // Read the value of N from standard input.

    // Declare a vector to keep track of the number of arrows currently
    // traveling at a specific height. The index of the vector represents
    // the height, and the value at that index represents the count of arrows.
    // The maximum possible height for a balloon is 1,000,000.
    // An arrow hitting a balloon at height H continues at H-1. The minimum
    // useful height for an arrow is 1 (to hit a balloon at height 1 and then
    // continue at height 0). So, we need to track heights from 0 up to 1,000,000.
    // A size of 1,000,000 + 1 (for 0-indexed access up to 1,000,000) is sufficient.
    // Initialize all counts to 0.
    std::vector<int> arrows_at_height(1000001, 0);

    int total_arrows_shot = 0; // Initialize a counter for the total number of arrows shot.

    // Iterate through each balloon from left to right. This greedy approach
    // works because an arrow can only decrease its height. To pop a balloon
    // at a certain height, an arrow must either be shot at that height or
    // have previously popped a higher balloon and descended to the current height.
    // By processing balloons from left to right, we ensure that any arrow
    // available at a certain height has already passed all balloons to its left.
    for (int i = 0; i < N; ++i) {
        int current_balloon_height; // Declare a variable to store the height of the current balloon.
        std::cin >> current_balloon_height; // Read the height of the current balloon.

        // Check if there is an arrow currently traveling at the exact height
        // of the current balloon.
        if (arrows_at_height[current_balloon_height] > 0) {
            // If an arrow is available at this height:
            // This is the optimal choice as it avoids shooting a new arrow.
            // 1. Decrement the count of arrows at the current balloon's height.
            //    This arrow is "used" to pop the balloon at this height.
            arrows_at_height[current_balloon_height]--;
            // 2. Increment the count of arrows at (current_balloon_height - 1).
            //    After popping the balloon, the arrow continues its path
            //    at a height decreased by 1. This arrow is now available
            //    for balloons at height (current_balloon_height - 1) further to the right.
            arrows_at_height[current_balloon_height - 1]++;
        } else {
            // If no arrow is available at the current balloon's height:
            // We have no choice but to shoot a new arrow to pop this balloon.
            // 1. Increment the total arrows shot count.
            total_arrows_shot++;
            // 2. This new arrow starts at current_balloon_height, pops the balloon,
            //    and then immediately continues at current_balloon_height - 1.
            //    So, we increment the count of arrows available at height (current_balloon_height - 1).
            arrows_at_height[current_balloon_height - 1]++;
        }
    }

    // After processing all balloons, the total_arrows_shot variable holds
    // the minimal number of times Perica needed to shoot an arrow.
    std::cout << total_arrows_shot << std::endl;

    return 0; // Indicate successful execution of the program.
}