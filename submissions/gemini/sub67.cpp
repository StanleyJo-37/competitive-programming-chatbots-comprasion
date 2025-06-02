#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector to store promo codes
#include <string>   // Required for std::string to handle promo codes
#include <algorithm> // Required for std::min function

// Function to calculate the Hamming distance between two 6-digit strings.
// The Hamming distance is the number of positions at which the corresponding
// symbols are different.
int calculateHammingDistance(const std::string& s1, const std::string& s2) {
    int distance = 0; // Initialize distance counter
    // Iterate through each character position (0 to 5) of the 6-digit strings.
    // Promo codes are guaranteed to be exactly six digits long.
    for (int i = 0; i < 6; ++i) {
        // If characters at the current position are different, increment distance.
        if (s1[i] != s2[i]) {
            distance++;
        }
    }
    return distance; // Return the calculated Hamming distance
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare variable to store the number of promo codes
    std::cin >> n; // Read the number of promo codes

    // Special case: If there is only one promo code.
    // If n=1, there are no other promo codes to be confused with.
    // Therefore, any typed code (up to 6 errors away) will uniquely identify
    // the single existing promo code. The maximum k is the length of the code, which is 6.
    if (n == 1) {
        std::cout << 6 << std::endl; // Print 6 and exit
        return 0;
    }

    // Declare a vector of strings to store all promo codes.
    std::vector<std::string> promo_codes(n);
    // Read each promo code into the vector.
    for (int i = 0; i < n; ++i) {
        std::cin >> promo_codes[i];
    }

    // Initialize min_dist to the maximum possible Hamming distance for 6 digits (which is 6).
    // This ensures that the first calculated distance will be smaller or equal,
    // correctly setting the initial minimum.
    int min_dist = 6; 

    // Iterate through all unique pairs of promo codes to find the minimum Hamming distance.
    // We use nested loops: the outer loop iterates from the first code to the second-to-last,
    // and the inner loop iterates from the code after the current outer loop code to the last.
    // This avoids comparing a code with itself and comparing the same pair twice (e.g., (P1, P2) and (P2, P1)).
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Calculate the Hamming distance between the current pair of promo codes.
            int current_dist = calculateHammingDistance(promo_codes[i], promo_codes[j]);
            // Update min_dist if the current_dist is smaller than the previously found minimum.
            min_dist = std::min(min_dist, current_dist);
            
            // Optimization: If min_dist becomes 1, it means there are two promo codes
            // that differ by only one digit. In this case, the maximum k will be
            // (1 - 1) / 2 = 0. No smaller positive distance is possible, so we can
            // stop further calculations as k cannot be greater than 0.
            if (min_dist == 1) {
                break; // Break the inner loop
            }
        }
        // If min_dist is already 1, we can break the outer loop as well.
        if (min_dist == 1) {
            break; // Break the outer loop
        }
    }

    // The problem asks for the maximum k such that any promo code can be uniquely
    // identified if typed with at most k errors. This means that for any two
    // distinct promo codes P_i and P_j, their "error spheres" of radius k must not overlap.
    // If the Hamming distance between P_i and P_j is D, then for their spheres
    // to be disjoint, we need D > 2k, or D >= 2k + 1.
    // From this, we derive 2k <= D - 1, which means k <= (D - 1) / 2.
    // To satisfy this condition for ALL pairs, we must use the minimum distance found (min_dist).
    // So, the maximum k is floor((min_dist - 1) / 2).
    // Integer division in C++ automatically performs floor for positive numbers.
    int k = (min_dist - 1) / 2;

    std::cout << k << std::endl; // Print the calculated maximum k

    return 0; // Indicate successful execution
}