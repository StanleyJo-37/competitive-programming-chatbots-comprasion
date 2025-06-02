#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the actions
#include <algorithm> // Required for std::min

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // preventing potential synchronization overhead.
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not
    // flush std::cout before reading input, which can speed up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k; // Declare variables for the total number of skewers (n) and the range of influence (k)
    std::cin >> n >> k; // Read the values of n and k from standard input

    // A vector to store the 1-based indices of the skewers that Miroslav decides to turn.
    // This will be our final list of actions.
    std::vector<int> actions;

    // 'current_skewer_to_cover' represents the leftmost skewer that is currently
    // in its initial state (not turned over) and needs to be turned.
    // We start by needing to turn skewer 1.
    int current_skewer_to_cover = 1;

    // The main loop continues as long as there are skewers (from 1 to n) that
    // still need to be turned over.
    while (current_skewer_to_cover <= n) {
        // This is the core of the greedy strategy:
        // To ensure 'current_skewer_to_cover' is turned, and to maximize the
        // reach of this single action to the right (covering as many subsequent
        // skewers as possible), Miroslav should choose to turn the skewer at
        // position 'current_skewer_to_cover + k'.
        //
        // When skewer 'p' is turned, it flips skewers in the range [p-k, p+k].
        // By choosing 'p = current_skewer_to_cover + k', the range becomes:
        // [ (current_skewer_to_cover + k) - k, (current_skewer_to_cover + k) + k ]
        // which simplifies to [ current_skewer_to_cover, current_skewer_to_cover + 2*k ].
        // This choice guarantees that 'current_skewer_to_cover' is flipped,
        // and it extends the coverage as far right as possible.
        int skewer_to_turn = current_skewer_to_cover + k;

        // Add the chosen skewer's index to our list of actions.
        actions.push_back(skewer_to_turn);

        // After performing this action, all skewers from 'current_skewer_to_cover'
        // up to 'skewer_to_turn + k' (or 'n', if 'skewer_to_turn + k' exceeds 'n')
        // are now considered turned.
        // Therefore, the next skewer that needs to be covered is the one immediately
        // after this newly covered segment.
        // We use std::min(n, skewer_to_turn + k) to ensure we don't consider skewers
        // beyond 'n' as part of the covered range for the purpose of advancing.
        // Adding 1 to this value gives us the first skewer that is potentially
        // still in its initial state and needs attention.
        current_skewer_to_cover = std::min(n, skewer_to_turn + k) + 1;
    }

    // Output the total number of actions (the size of the 'actions' vector).
    std::cout << actions.size() << std::endl;

    // Output the indices of the skewers that were chosen to be turned,
    // separated by spaces.
    for (size_t i = 0; i < actions.size(); ++i) {
        std::cout << actions[i] << (i == actions.size() - 1 ? "" : " ");
    }
    std::cout << std::endl; // Newline after printing all actions

    return 0; // Indicate successful program execution
}