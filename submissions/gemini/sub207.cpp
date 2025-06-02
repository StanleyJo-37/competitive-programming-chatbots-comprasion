#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
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

    std::vector<long long> diff(n);
    for (int i = 0; i < n; ++i) {
        diff[i] = a[i] - b[i];
    }

    std::sort(diff.begin(), diff.end());

    long long count = 0;
    for (int i = 0; i < n; ++i) {
        long long target = -diff[i];
        // Find the first element greater than target
        auto it = std::upper_bound(diff.begin() + i + 1, diff.end(), target);
        count += std::distance(it, diff.end());
    }

    std::cout << count << std::endl;

    return 0;
}