#include <iostream>
#include <algorithm> // For std::max and std::min
#include <vector>    // For std::vector (though not strictly necessary, can use individual variables)

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long b, d, s;
    // Read the number of breakfasts, dinners, and suppers Vasiliy had.
    std::cin >> b >> d >> s;

    // Initialize minimum missed meals to a very large value.
    // We will update this with the minimum found across all possible scenarios.
    // Using a value larger than any possible result (e.g., 3 * 10^18) or a sentinel.
    // Since we are minimizing, a large initial value is appropriate.
    long long min_missed_meals = -1; // Sentinel value, will be updated on first calculation

    // The core idea is that the number of available breakfasts (N_B), dinners (N_D),
    // and suppers (N_S) during Vasiliy's stay must be "close" to each other.
    // Specifically, the maximum difference between any two of N_B, N_D, N_S
    // can be at most 1. For example, (k, k, k), (k+1, k, k), (k+1, k+1, k), etc.
    // This is because meals occur in a fixed order (Breakfast, Dinner, Supper) daily.
    // If Vasiliy misses a meal type, it's either because he arrived after it
    // on the first day, or left before it on the last day. Each such event
    // can only affect the count of one or two meal types by one.
    // For instance, if he had N_D dinners but N_S suppers, then N_D - N_S can be at most 1
    // (if he left after dinner but before supper on the last day).
    // Similarly, N_B - N_D can be at most 1.
    // Also, N_D - N_B can be at most 1 (if he arrived after breakfast but before dinner on the first day).
    // And N_S - N_D can be at most 1.
    // These constraints imply that max(N_B, N_D, N_S) - min(N_B, N_D, N_S) <= 1.

    // We iterate through 6 possible patterns for (N_B, N_D, N_S) based on
    // which meal type has the maximum count (let's call it X) and which have (X-1).
    // For each pattern, we determine the minimum X required to satisfy
    // N_B >= b, N_D >= d, N_S >= s, and then calculate the missed meals.

    // Pattern 1: (X, X, X)
    // All meal types are available X times. This implies Vasiliy arrived before
    // breakfast and left after supper (or before breakfast the next day).
    // To satisfy b <= X, d <= X, s <= X, X must be at least max(b, d, s).
    {
        long long X = std::max({b, d, s}); // C++11 initializer list for std::max
        long long current_N_B = X;
        long long current_N_D = X;
        long long current_N_S = X;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Pattern 2: (X, X, X-1)
    // Breakfast and Dinner available X times, Supper available X-1 times.
    // This implies Vasiliy arrived before breakfast and left after dinner.
    // To satisfy b <= X, d <= X, s <= X-1:
    // X must be at least b, at least d, and at least s+1.
    // So, X = max(b, d, s+1).
    {
        long long X = std::max({b, d, s + 1});
        long long current_N_B = X;
        long long current_N_D = X;
        long long current_N_S = X - 1;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Pattern 3: (X, X-1, X-1)
    // Breakfast available X times, Dinner and Supper available X-1 times.
    // This implies Vasiliy arrived before breakfast and left after breakfast.
    // To satisfy b <= X, d <= X-1, s <= X-1:
    // X must be at least b, at least d+1, and at least s+1.
    // So, X = max(b, d+1, s+1).
    {
        long long X = std::max({b, d + 1, s + 1});
        long long current_N_B = X;
        long long current_N_D = X - 1;
        long long current_N_S = X - 1;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Pattern 4: (X-1, X, X)
    // Breakfast available X-1 times, Dinner and Supper available X times.
    // This implies Vasiliy arrived before dinner and left after supper.
    // To satisfy b <= X-1, d <= X, s <= X:
    // X must be at least b+1, at least d, and at least s.
    // So, X = max(b+1, d, s).
    {
        long long X = std::max({b + 1, d, s});
        long long current_N_B = X - 1;
        long long current_N_D = X;
        long long current_N_S = X;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Pattern 5: (X-1, X, X-1)
    // Breakfast available X-1 times, Dinner available X times, Supper available X-1 times.
    // This implies Vasiliy arrived before dinner and left after dinner.
    // To satisfy b <= X-1, d <= X, s <= X-1:
    // X must be at least b+1, at least d, and at least s+1.
    // So, X = max(b+1, d, s+1).
    {
        long long X = std::max({b + 1, d, s + 1});
        long long current_N_B = X - 1;
        long long current_N_D = X;
        long long current_N_S = X - 1;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Pattern 6: (X-1, X-1, X)
    // Breakfast and Dinner available X-1 times, Supper available X times.
    // This implies Vasiliy arrived before supper and left after supper.
    // To satisfy b <= X-1, d <= X-1, s <= X:
    // X must be at least b+1, at least d+1, and at least s.
    // So, X = max(b+1, d+1, s).
    {
        long long X = std::max({b + 1, d + 1, s});
        long long current_N_B = X - 1;
        long long current_N_D = X - 1;
        long long current_N_S = X;
        long long missed = (current_N_B - b) + (current_N_D - d) + (current_N_S - s);
        if (min_missed_meals == -1 || missed < min_missed_meals) {
            min_missed_meals = missed;
        }
    }

    // Print the minimum number of missed meals found.
    std::cout << min_missed_meals << std::endl;

    return 0;
}