#include <iostream>
#include <vector>
#include <algorithm> // For std::sort and std::upper_bound

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of enemies
    int p; // Prime number
    std::cin >> n >> p;

    std::vector<int> a(n); // Candies of enemies
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Sort the enemy candy values in non-decreasing order.
    // This is crucial because Yuzu's ability to win depends on the relative difficulty
    // of enemies and her increasing candy count. Sorting simplifies the logic for f(x).
    std::sort(a.begin(), a.end());

    // Calculate min_x: the minimum initial candies Yuzu needs to be able to win all duels.
    // For a permutation P to be valid, Yuzu must be able to defeat enemy P_k at step k.
    // At step k, Yuzu has x + (k-1) candies (assuming she won k-1 previous duels).
    // So, she must satisfy x + (k-1) >= a_{P_k}.
    // To guarantee that at least one valid permutation exists, for each k from 1 to n,
    // there must be at least k enemies she can defeat with x + (k-1) candies.
    // This means that the k-th smallest enemy (a[k-1] in 0-indexed sorted array)
    // must be defeatable by her at step k, i.e., a[k-1] <= x + (k-1).
    // Rearranging, x >= a[k-1] - (k-1).
    // Thus, x must be greater than or equal to the maximum of these values for all k.
    int min_x = 0; // Initialize with a value that will be overwritten by max
    for (int i = 0; i < n; ++i) {
        // a[i] is the (i+1)-th smallest enemy.
        // At step (i+1), Yuzu has x + i candies.
        // She must be able to defeat a[i], so x + i >= a[i].
        // This implies x >= a[i] - i.
        min_x = std::max(min_x, a[i] - i);
    }

    // According to the problem statement, x must be a positive integer.
    // So, the minimum possible x is 1.
    min_x = std::max(1, min_x);

    // Determine the maximum x to check.
    // If x >= a[n-1] (the largest enemy's candy count), then Yuzu can defeat all enemies
    // even at the first step (x >= a[n-1] implies x >= a_i for all i).
    // In this case, for any k, x + (k-1) >= a[n-1] (since k-1 >= 0).
    // So, count_k (number of enemies <= x+k-1) will be n for all k.
    // f(x) = product_{k=1 to n} (n - (k-1)) = product_{j=1 to n} j = n!.
    // Since p is a prime number and p <= n, p is a factor of n!.
    // Therefore, n! is divisible by p, meaning f(x) % p == 0 for x >= a[n-1].
    // So, such x values are not "good".
    // We only need to check x values up to a[n-1] - 1.
    int max_x_to_check = a[n - 1] - 1;

    std::vector<int> good_x_values; // Store all good x values

    // Iterate through possible x values.
    // The range is [min_x, max_x_to_check].
    // If min_x > max_x_to_check, it means there are no good x values in this range.
    for (int x = min_x; x <= max_x_to_check; ++x) {
        bool is_x_good = true; // Assume x is good until proven otherwise

        // Check the condition for f(x) % p != 0.
        // f(x) = product_{k=1 to n} (count_k - (k-1))
        // where count_k is the number of enemies j such that a_j <= x + (k-1).
        // For f(x) % p != 0, each term (count_k - (k-1)) must not be divisible by p.
        for (int k = 1; k <= n; ++k) {
            // Calculate the threshold for the k-th duel.
            int current_candy_threshold = x + (k - 1);

            // Find count_k: number of enemies with candies <= current_candy_threshold.
            // std::upper_bound returns an iterator to the first element strictly greater than current_candy_threshold.
            // Subtracting a.begin() gives the 0-based index, which is equivalent to the count.
            int count_k = std::upper_bound(a.begin(), a.end(), current_candy_threshold) - a.begin();

            // Calculate the number of choices for the k-th enemy.
            // This is count_k (total enemies defeatable with current candies)
            // minus (k-1) (enemies already defeated in previous steps).
            int choices_for_kth_duel = count_k - (k - 1);

            // If choices_for_kth_duel is less than 1, it means Yuzu cannot win all duels
            // with this x, so f(x) = 0. This case is already covered by min_x calculation,
            // as we iterate x from min_x, choices_for_kth_duel will always be >= 1.
            // The critical condition for f(x) % p != 0 is that this term is not divisible by p.
            if (choices_for_kth_duel % p == 0) {
                is_x_good = false; // f(x) will be divisible by p
                break; // No need to check further for this x
            }
        }

        if (is_x_good) {
            good_x_values.push_back(x);
        }
    }

    // Output the results.
    std::cout << good_x_values.size() << "\n";
    for (size_t i = 0; i < good_x_values.size(); ++i) {
        std::cout << good_x_values[i] << (i == good_x_values.size() - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}