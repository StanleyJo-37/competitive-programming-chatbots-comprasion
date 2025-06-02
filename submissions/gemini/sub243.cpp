#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::vector<long long> d_min(n);
    std::vector<long long> d_max(n);

    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (b[j] < a[i]) {
            j++;
        }
        d_min[i] = b[j] - a[i];
    }

    std::multiset<long long> current_b_elements;
    for (int i = 0; i < n; ++i) {
        current_b_elements.insert(b[i]);
    }

    for (int i = 0; i < n; ++i) {
        d_max[i] = (*current_b_elements.rbegin()) - a[i];
        current_b_elements.erase(current_b_elements.find(b[i]));
        if (i + 1 < n) {
            long long required_b_val = a[i+1];
            current_b_elements.erase(current_b_elements.find_first_of(current_b_elements.lower_bound(required_b_val), current_b_elements.end()));
        }
    }


    for (int i = 0; i < n; ++i) {
        std::cout << d_min[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << d_max[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}