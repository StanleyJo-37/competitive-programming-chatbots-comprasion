#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for using std::string to store the color configuration
#include <algorithm> // Required for std::min (used to find the minimum of three values)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare an integer variable T to store the number of test cases.
    std::cin >> T; // Read the number of test cases from standard input.

    // Loop through each test case.
    while (T--) {
        int N; // Declare an integer variable N to store the number of rooms.
        std::cin >> N; // Read the number of rooms for the current test case.

        std::string S; // Declare a string variable S to store the current color configuration.
        std::cin >> S; // Read the color configuration string.

        // Initialize counters for each color.
        int countR = 0; // Counter for 'R' (Red) rooms.
        int countG = 0; // Counter for 'G' (Green) rooms.
        int countB = 0; // Counter for 'B' (Blue) rooms.

        // Iterate through the string S to count occurrences of each color.
        for (char c : S) {
            if (c == 'R') {
                countR++; // Increment count for Red rooms.
            } else if (c == 'G') {
                countG++; // Increment count for Green rooms.
            } else { // If not 'R' or 'G', it must be 'B'
                countB++; // Increment count for Blue rooms.
            }
        }

        // The problem asks for the minimum number of rooms to repaint so that all rooms
        // have the same color. There are three possible target colors for the entire house:
        // Red, Green, or Blue. We need to calculate the cost (number of repaints) for each
        // target color and then choose the minimum among them.
        //
        // The painting rules state that mixing any two colors results in the third color.
        // For example, R + B = G. This implies that if a room's current color is C and
        // you apply paint P, the resulting color T will be the third color distinct from C and P.
        //
        // Crucially, if a room's current color is different from the desired target color,
        // it will always require exactly one repaint operation. The specific paint color
        // to achieve the target doesn't matter for the count, only that a repaint is needed.
        //
        // For example, if a room is 'R' and the target is 'B':
        // Applying 'G' paint (R + G = B) will make it 'B'. This counts as 1 repaint.
        //
        // Therefore, the number of rooms needing repainting to achieve a specific target color
        // is simply the total number of rooms minus the number of rooms that are already
        // that target color.
        //
        // 1. Cost if all rooms become 'R' (Red):
        //    Rooms that are already 'R' do not need repainting.
        //    Rooms that are 'G' or 'B' need repainting.
        //    Cost = (countG + countB) which is equivalent to N - countR.
        //
        // 2. Cost if all rooms become 'G' (Green):
        //    Rooms that are already 'G' do not need repainting.
        //    Rooms that are 'R' or 'B' need repainting.
        //    Cost = (countR + countB) which is equivalent to N - countG.
        //
        // 3. Cost if all rooms become 'B' (Blue):
        //    Rooms that are already 'B' do not need repainting.
        //    Rooms that are 'R' or 'G' need repainting.
        //    Cost = (countR + countG) which is equivalent to N - countB.

        // Calculate the cost for each possible target color.
        int cost_to_make_all_R = N - countR; // Number of rooms not 'R'
        int cost_to_make_all_G = N - countG; // Number of rooms not 'G'
        int cost_to_make_all_B = N - countB; // Number of rooms not 'B'

        // Find the minimum among these three costs.
        // std::min can take an initializer list {a, b, c} in C++11 and later.
        int min_repaints = std::min({cost_to_make_all_R, cost_to_make_all_G, cost_to_make_all_B});

        // Print the minimum number of repaints for the current test case, followed by a newline.
        std::cout << min_repaints << "\n";
    }

    return 0; // Indicate successful execution of the program.
}