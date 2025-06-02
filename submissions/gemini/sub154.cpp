#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

long long calculate_g(int x, int y, const std::vector<int>& a) {
    long long total_g = 0;
    for (int i = x; i <= y; ++i) {
        for (int j = i; j <= y; ++j) {
            int current_xor = 0;
            for (int k = i; k <= j; ++k) {
                current_xor ^= a[k];
            }
            total_g += current_xor;
        }
    }
    return total_g;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int qi = 0; qi < q; ++qi) {
        int x, y, k;
        std::cin >> x >> y >> k;

        long long max_g = 0;

        int num_elements_in_range = y - x + 1;

        std::vector<int> p(num_elements_in_range);
        std::iota(p.begin(), p.end(), 0);

        long long current_g = 0;
        
        // Calculate initial g
        current_g = calculate_g(x, y, a);
        max_g = current_g;

        if (k > 0) {
            std::vector<int> current_a = a;
            std::vector<int> indices_to_change;

            std::vector<std::pair<long long, int>> potential_changes; // {delta_g, index_in_range}

            for (int i = x; i <= y; ++i) {
                // Try flipping a[i] and see the delta_g
                current_a[i] ^= 1; // Flip the bit
                long long new_g = calculate_g(x, y, current_a);
                current_a[i] ^= 1; // Flip back

                potential_changes.push_back({new_g - current_g, i});
            }

            std::sort(potential_changes.rbegin(), potential_changes.rend());

            for (int i = 0; i < std::min((int)potential_changes.size(), k); ++i) {
                if (potential_changes[i].first > 0) {
                    current_g += potential_changes[i].first;
                    current_a[potential_changes[i].second] ^= 1;
                } else {
                    break; 
                }
            }
            max_g = std::max(max_g, current_g);
        }
        std::cout << max_g << std::endl;
    }

    return 0;
}