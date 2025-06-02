#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void solve() {
    // n: maximum possible number of rounds
    // k: points threshold for losing
    int n;
    long long k;
    std::cin >> n >> k;

    // a_j: points human gains in round j
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // b_j: points computer gains in round j
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    // human_score: current points of the human player
    long long human_score = 0;
    // computer_score: current points of the computer player
    long long computer_score = 0;
    // reset_rounds: stores the 1-indexed round numbers where a reset occurred
    std::vector<int> reset_rounds;

    // Iterate through each round
    for (int i = 0; i < n; ++i) {
        // Add points for the current round (round i+1)
        human_score += a[i];
        computer_score += b[i];

        // Check for win condition: computer reaches k points or more, and human has less than k points.
        if (computer_score >= k && human_score < k) {
            // Human wins! Print the number of resets and the rounds where resets occurred.
            std::cout << reset_rounds.size() << std::endl;
            for (size_t j = 0; j < reset_rounds.size(); ++j) {
                std::cout << reset_rounds[j] << (j == reset_rounds.size() - 1 ? "" : " ");
            }
            std::cout << std::endl;
            return; // Game ends, move to next test case.
        }

        // Check for forced reset: human score reaches or exceeds k.
        // If human_score >= k, human would lose (or both would lose if computer_score also >= k).
        // To avoid losing, a reset is mandatory at the end of this round.
        if (human_score >= k) {
            // Before performing the reset, check if winning is still possible.
            // A reset transforms (x, y) to (max(0, x-y), max(0, y-x)).
            // If human_score >= computer_score, new human_score is human_score - computer_score.
            // If human_score - computer_score is still >= k, then human loses even after reset.
            // If human_score < computer_score, new human_score is 0, which is always < k (since k >= 2).
            // So, the only impossible case is when human_score >= computer_score AND human_score - computer_score >= k.
            // This condition implies human_score >= k + computer_score, which means human_score is already >= k.
            // Thus, the check simplifies to: if (human_score - computer_score >= k).
            if (human_score - computer_score >= k) {
                // Even after reset, human score would be >= k. Impossible to win.
                std::cout << -1 << std::endl;
                return; // Game ends, move to next test case.
            }
            
            // Perform the reset:
            // Record the current round number (1-indexed) as a reset round.
            reset_rounds.push_back(i + 1); 
            
            // Calculate new scores after reset.
            long long new_human_score = std::max(0LL, human_score - computer_score);
            long long new_computer_score = std::max(0LL, computer_score - human_score);
            
            // Update current scores.
            human_score = new_human_score;
            computer_score = new_computer_score;
        }
        // If human_score < k and computer_score < k, and no win condition met,
        // the game continues. The greedy strategy is to only reset when forced.
        // Resetting otherwise would incur an extra cost (1 reset) without immediate necessity,
        // and it reduces total points, potentially making it harder for the computer to reach k
        // or requiring more rounds. This greedy choice aims for the minimum number of resets.
    }

    // If the loop finishes (all n rounds played) and no win condition was met,
    // it means both players have less than k points, resulting in a tie.
    // Since the problem asks for a win, a tie is not a successful outcome.
    std::cout << -1 << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties cin from cout, meaning cin will not flush cout before reading input.
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}
