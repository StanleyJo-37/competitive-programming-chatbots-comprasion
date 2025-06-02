#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Function to compute gcd of two numbers
long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;

        // Store the numeric values of each character in S
        vector<int> vals(N);
        for (int i = 0; i < N; ++i) {
            vals[i] = S[i] - 'a' + 1;
        }

        // Sort in descending order to maximize sum of numbers if needed
        sort(vals.rbegin(), vals.rend());

        // Precompute prefix sums for quick sum calculation
        vector<long long> prefix(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            prefix[i + 1] = prefix[i] + vals[i];
        }

        // We want to maximize:
        // P = (N - x) - x + (sum_of_x_largest_numbers / K)
        //   = N - 2x + (sum_of_x_largest_numbers / K)
        // Try all possible x (number of replaced letters)
        long long best_num = N, best_den = 1; // Start with x = 0 (no replacements)
        for (int x = 0; x <= N; ++x) {
            // sum_of_x_largest_numbers = prefix[x]
            long long num = N - 2 * x; // integer part
            long long sum = prefix[x];
            // Add the fractional part
            num = num * K + sum; // numerator
            long long den = K;   // denominator

            // Reduce fraction
            long long g = gcd(abs(num), den);
            num /= g;
            den /= g;

            // Compare with current best (maximize num/den)
            // Cross multiply to avoid floating point
            if (best_num * den < num * best_den) {
                best_num = num;
                best_den = den;
            }
        }

        cout << best_num << " " << best_den << endl;
    }
    return 0;
}