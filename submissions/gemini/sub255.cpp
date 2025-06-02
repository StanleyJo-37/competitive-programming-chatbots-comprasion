#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store energies
#include <iomanip>  // Required for std::fixed and std::setprecision for output formatting
#include <algorithm> // Required for std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin,
    // leading to faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of distinct states
    long long U; // Maximum allowed energy difference E_k - E_i
    std::cin >> n >> U;

    std::vector<long long> E(n); // Vector to store energies E_1, E_2, ..., E_n
    for (int i = 0; i < n; ++i) {
        std::cin >> E[i];
    }

    double max_eta = -1.0; // Initialize maximum efficiency to -1.0.
                           // This value also serves as a flag to indicate if any valid triplet was found.

    // k_ptr will be the right pointer in the two-pointer approach.
    // It tracks the potential index for state k.
    // It starts at index 2 because the minimum k for i=0, j=1 is k=2 (since i < j < k).
    int k_ptr = 2; 

    // Iterate through possible indices for state i.
    // The index i can go from 0 up to n-3.
    // If i is n-3, then j=i+1=n-2, and k=i+2=n-1. This is the last possible triplet (n-3, n-2, n-1)
    // that satisfies i < j < k and uses valid indices within the E array.
    for (int i = 0; i < n - 2; ++i) {
        // For a fixed i, we want to choose j such that i < j < k.
        // The energy conversion efficiency is eta = (E_k - E_j) / (E_k - E_i).
        // This can be rewritten as eta = 1 - (E_j - E_i) / (E_k - E_i).
        // To maximize eta, we need to minimize the term (E_j - E_i) / (E_k - E_i).
        // For a fixed i and k, E_k - E_i is constant.
        // Thus, we need to minimize E_j - E_i.
        // Since E_j must be greater than E_i (because j > i and energies are increasing),
        // the smallest possible value for E_j is E_{i+1}.
        // Therefore, we fix j = i+1.
        int j = i + 1;

        // Move k_ptr forward to find the largest valid k for the current i.
        // We need E_k - E_i <= U.
        // The two-pointer approach works because as i increases, E[i] increases.
        // This means E[i] + U also increases, allowing k_ptr to potentially move further right.
        // Since both i and k_ptr only move forward, the total complexity of this nested loop structure is O(N).
        while (k_ptr < n && E[k_ptr] - E[i] <= U) {
            k_ptr++;
        }
        
        // After the while loop, k_ptr is the first index such that E[k_ptr] - E[i] > U,
        // or k_ptr is n (meaning all remaining elements satisfy the condition).
        // The largest valid k for the current i is k_ptr - 1.
        int best_k = k_ptr - 1;

        // Check if a valid k was found for the current i.
        // A valid k must satisfy k > j (which is i+1), so k must be at least i+2.
        // If best_k is less than i+2, it means no valid k exists for this i that satisfies i < j < k.
        if (best_k >= i + 2) {
            // Calculate the efficiency for the triplet (i, j, best_k).
            // We use static_cast<double> to ensure floating-point division.
            double current_eta = static_cast<double>(E[best_k] - E[j]) / (E[best_k] - E[i]);
            // Update the maximum efficiency found so far.
            max_eta = std::max(max_eta, current_eta);
        }
    }

    // Output the result.
    // If max_eta is still -1.0, it means no valid triplet (i, j, k) was found
    // that satisfies all constraints (i < j < k and E_k - E_i <= U).
    if (max_eta == -1.0) {
        std::cout << -1 << std::endl;
    } else {
        // Print the maximum efficiency with the required precision (10 decimal places).
        std::cout << std::fixed << std::setprecision(10) << max_eta << std::endl;
    }

    return 0; // Indicate successful program execution
}
