#include <iostream>
#include <string>
#include <vector>
#include <numeric> // For std::accumulate if needed, but simple loop is better.

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of rounds.

    std::string s;
    std::cin >> s; // Read the string of symbols.

    long long plus_count = 0;  // Count of '+' symbols.
    long long minus_count = 0; // Count of '-' symbols.

    // Iterate through the string to count '+' and '-' symbols.
    for (char c : s) {
        if (c == '+') {
            plus_count++;
        } else {
            minus_count++;
        }
    }

    // K represents the difference between the total count of '-' and '+' symbols.
    // This value is crucial for the score equation.
    long long K = minus_count - plus_count;

    int q;
    std::cin >> q; // Read the number of controllers (queries).

    // Process each query.
    for (int i = 0; i < q; ++i) {
        long long a, b;
        std::cin >> a >> b; // Read the button values for the current controller.

        // Case 1: The two buttons have the same value.
        // If a = b, then pressing either button has the same effect.
        // The total score will be (plus_count * a) - (minus_count * a)
        // which simplifies to (plus_count - minus_count) * a.
        // For the score to be 0, since a >= 1, we must have plus_count - minus_count = 0,
        // i.e., plus_count = minus_count.
        if (a == b) {
            if (plus_count == minus_count) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else {
            // Case 2: The two buttons have different values (a != b).
            // Let p_a be the number of '+' rounds where button 'a' is pressed.
            // Let m_a be the number of '-' rounds where button 'a' is pressed.
            // Then p_b = plus_count - p_a (number of '+' rounds where button 'b' is pressed).
            // And m_b = minus_count - m_a (number of '-' rounds where button 'b' is pressed).
            // The total score is:
            // (p_a * a + p_b * b) - (m_a * a + m_b * b) = 0
            // Substitute p_b and m_b:
            // (p_a * a + (plus_count - p_a) * b) - (m_a * a + (minus_count - m_a) * b) = 0
            // Expand and rearrange:
            // p_a * a + plus_count * b - p_a * b - m_a * a - minus_count * b + m_a * b = 0
            // Group terms by (a - b):
            // (p_a - m_a) * a + (plus_count - p_a - minus_count + m_a) * b = 0
            // (p_a - m_a) * a + (plus_count - minus_count - (p_a - m_a)) * b = 0
            // Let D = p_a - m_a. This D represents the net difference in times button 'a' is chosen
            // in '+' rounds versus '-' rounds.
            // D * a + (-(minus_count - plus_count) - D) * b = 0
            // D * a + (-K - D) * b = 0
            // D * a - K * b - D * b = 0
            // D * (a - b) = K * b
            // So, D = (K * b) / (a - b).

            long long diff_ab = a - b; // Denominator (a - b).
            long long numerator = K * b; // Numerator (K * b).

            // Check if numerator is divisible by diff_ab.
            // If not divisible, D is not an integer, so no solution exists.
            if (numerator % diff_ab != 0) {
                std::cout << "NO\n";
            } else {
                long long D = numerator / diff_ab; // Calculate D.

                // D = p_a - m_a.
                // We need to find if there exist integers p_a and m_a such that:
                // 0 <= p_a <= plus_count
                // 0 <= m_a <= minus_count
                // p_a - m_a = D
                // From p_a = D + m_a, substitute into p_a constraints:
                // 0 <= D + m_a <= plus_count
                // This implies -D <= m_a <= plus_count - D.
                // Combining with 0 <= m_a <= minus_count:
                // We need an integer m_a such that:
                // max(0, -D) <= m_a <= min(minus_count, plus_count - D).
                // Such an m_a exists if and only if max(0, -D) <= min(minus_count, plus_count - D).
                // This simplifies to two conditions:
                // 1. -D <= minus_count  => D >= -minus_count
                // 2. 0 <= plus_count - D => D <= plus_count
                // So, we need -minus_count <= D <= plus_count.
                if (D >= -minus_count && D <= plus_count) {
                    std::cout << "YES\n";
                } else {
                    std::cout << "NO\n";
                }
            }
        }
    }

    return 0;
}
