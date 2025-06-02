#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <map>

// Function to solve a single test case
void solve() {
    int n, q;
    std::cin >> n >> q; // Read n and q

    std::string s;
    std::cin >> s; // Read the string s representing charges

    std::vector<int> effective_charges(n);
    for (int i = 0; i < n; ++i) {
        int charge = (s[i] == '+') ? 1 : -1;
        if ((i + 1) % 2 == 1) { // 1-based index is odd, so it gets a + sign
            effective_charges[i] = charge;
        } else { // 1-based index is even, so it gets a - sign
            effective_charges[i] = -charge;
        }
    }

    std::vector<int> pref_sum_odd_idx(n + 1, 0); // Stores sum for (original 1-based index) 1, 3, 5...
    std::vector<int> pref_sum_even_idx(n + 1, 0); // Stores sum for (original 1-based index) 2, 4, 6...

    for (int i = 0; i < n; ++i) {
        int charge = (s[i] == '+') ? 1 : -1;
        pref_sum_odd_idx[i + 1] = pref_sum_odd_idx[i];
        pref_sum_even_idx[i + 1] = pref_sum_even_idx[i];
        if ((i + 1) % 2 == 1) { // 1-based index is odd
            pref_sum_odd_idx[i + 1] += charge;
        } else { // 1-based index is even
            pref_sum_even_idx[i + 1] += charge;
        }
    }

    for (int k = 0; k < q; ++k) {
        int l, r;
        std::cin >> l >> r; // Read l and r for the current query

        long long current_sum = 0;
        if (l % 2 == 1) { // If l is odd, first element gets a '+' sign
            current_sum = (long long)(pref_sum_odd_idx[r] - pref_sum_odd_idx[l - 1]) -
                          (long long)(pref_sum_even_idx[r] - pref_sum_even_idx[l - 1]);
        } else { // If l is even, first element gets a '+' sign, but it's an even original index
            current_sum = (long long)(pref_sum_even_idx[r] - pref_sum_even_idx[l - 1]) -
                          (long long)(pref_sum_odd_idx[r] - pref_sum_odd_idx[l - 1]);
        }

        if (current_sum == 0) {
            std::cout << 0 << "\n";
        } else if (current_sum % 2 != 0) {
            long long current_len = r - l + 1;
            if (current_sum == 0) {
                std::cout << 0 << "\n";
            } else if (current_len % 2 == 1) { // If length is odd
                std::cout << 1 << "\n";
            } else { // If length is even
                std::cout << 2 << "\n";
            }
        }
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}