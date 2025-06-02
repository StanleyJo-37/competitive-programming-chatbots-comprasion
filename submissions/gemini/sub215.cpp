#include <iostream>
#include <vector>
#include <algorithm> // For std::max

// Function to check if a given maximum candy limit K is achievable
bool check(long long K, int N, long long M, const std::vector<long long>& A, const std::vector<long long>& B) {
    // total_balloons_needed will store the minimum number of balloons required
    // to ensure that the candies paid on any day do not exceed K.
    long long total_balloons_needed = 0;

    // Iterate through each day
    for (int i = 0; i < N; ++i) {
        // If B_i is 0, then the candies paid on day i (C_i = max(0, A_i - X_i) * 0) will always be 0.
        // Since 0 <= K (K is non-negative), this condition is always met.
        // To minimize the total balloons used, we should give 0 balloons on this day (X_i = 0).
        // This contributes 0 to total_balloons_needed.
        if (B[i] == 0) {
            // No balloons needed for this day to satisfy the candy limit K.
            // We effectively give 0 balloons (X_i = 0) and pay 0 candies.
        } else {
            // If B_i > 0, we need to calculate the minimum X_i (balloons to give)
            // such that C_i = max(0, A_i - X_i) * B_i <= K.
            // This implies A_i - X_i <= K / B_i (integer division).
            // Let 'deficit' be A_i - X_i. We want to maximize 'deficit' to minimize X_i.
            // The maximum allowed deficit is K / B_i.
            // However, the actual deficit cannot exceed A_i (because X_i cannot be negative).
            // The number of balloons given X_i must be non-negative.
            // So, X_i = A_i - deficit. To minimize X_i, we maximize deficit.
            // The maximum deficit we can afford is K / B[i].
            // The number of balloons we must give is A[i] - (K / B[i]).
            // If this value is negative, it means K / B[i] is greater than or equal to A[i].
            // In this scenario, we can afford to have a deficit of A[i] (i.e., give 0 balloons)
            // and still satisfy the candy limit K. So, X_i = 0.
            long long max_deficit_allowed = K / B[i];
            long long balloons_for_day_i = A[i] - max_deficit_allowed;

            // Ensure balloons_for_day_i is not negative. If it's negative, it means
            // we can give 0 balloons and still satisfy the candy limit.
            balloons_for_day_i = std::max(0LL, balloons_for_day_i);
            
            // Add the balloons needed for this day to the total.
            total_balloons_needed += balloons_for_day_i;

            // Optimization: If total_balloons_needed already exceeds M,
            // then this K is not achievable, so we can stop early.
            // This also prevents potential overflow if total_balloons_needed
            // were to grow extremely large, though with N*A_i_max = 10^14,
            // it fits in long long before comparison with M (10^18).
            if (total_balloons_needed > M) {
                return false;
            }
        }
    }

    // Return true if the total balloons needed is within the available M,
    // meaning K is an achievable maximum candy limit.
    return total_balloons_needed <= M;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N; // Number of days
    long long M; // Total available balloons
    std::cin >> N >> M;

    // Vectors to store A_i (balloons wanted) and B_i (candies per deficit balloon)
    std::vector<long long> A(N);
    std::vector<long long> B(N);

    // Read A_i values
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    // Read B_i values
    for (int i = 0; i < N; ++i) {
        std::cin >> B[i];
    }

    // Binary search for the minimum possible maximum number of candies (K).
    // The search space for K ranges from 0 to a maximum possible value.
    // Max A_i * Max B_i = 10^9 * 10^9 = 10^18.
    // So, a safe upper bound for K is 2 * 10^18.
    long long low = 0;
    long long high = 2e18; // Upper bound for K.
    long long ans = high;   // Initialize answer with a value that is definitely achievable (or max possible).

    // Standard binary search loop
    while (low <= high) {
        long long mid = low + (high - low) / 2; // Calculate mid to prevent potential overflow of (low + high)
        
        // If 'mid' is an achievable maximum candy limit,
        // it means we might be able to do even better (smaller K).
        // So, we store 'mid' as a potential answer and try the lower half.
        if (check(mid, N, M, A, B)) {
            ans = mid;
            high = mid - 1;
        } else {
            // If 'mid' is not an achievable maximum candy limit,
            // it means we need to allow more candies.
            // So, we search in the upper half.
            low = mid + 1;
        }
    }

    // Print the minimum achievable maximum candy limit.
    std::cout << ans << std::endl;

    return 0;
}