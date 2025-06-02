#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long inv(long long n, long long mod) {
    return power(n, mod - 2, mod);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> points(2 * n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].first;
        points[i].second = 1; // From sequence a
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> points[n + i].first;
        points[n + i].second = 2; // From sequence b
    }

    long long m;
    std::cin >> m;

    std::sort(points.begin(), points.end());

    std::map<int, int> count_a;
    std::map<int, int> count_b;
    std::map<int, int> count_both;

    for (int i = 0; i < n; ++i) {
        count_a[points[i].first]++;
    }
    for (int i = 0; i < n; ++i) {
        count_b[points[n + i].first]++;
    }

    for (const auto& pair_a : count_a) {
        if (count_b.count(pair_a.first)) {
            count_both[pair_a.first] = std::min(pair_a.second, count_b[pair_a.first]);
        }
    }

    long long ans = 1;
    std::vector<long long> fact(2 * n + 1);
    fact[0] = 1;
    for (int i = 1; i <= 2 * n; ++i) {
        fact[i] = (fact[i - 1] * i) % m;
    }

    for (int i = 0; i < 2 * n; ) {
        int j = i;
        while (j < 2 * n && points[j].first == points[i].first) {
            j++;
        }
        int current_val = points[i].first;
        int current_count = j - i;

        ans = (ans * fact[current_count]) % m;

        if (count_both.count(current_val)) {
            int common = count_both[current_val];
            ans = (ans * inv(fact[common], m)) % m;
        }

        bool has_duplicate_pair = false;
        if (count_a.count(current_val) && count_b.count(current_val)) {
            if (count_a[current_val] == count_b[current_val]) {
                has_duplicate_pair = true;
            }
        }
        
        if (has_duplicate_pair) {
             ans = (ans * inv(2,m)) % m;
        }

        i = j;
    }
    
    std::map<std::pair<int, int>, int> exact_duplicates;
    for (const auto& p : points) {
        exact_duplicates[p]++;
    }

    for (const auto& pair : exact_duplicates) {
        if (pair.second > 1) {
            ans = (ans * inv(fact[pair.second], m)) % m;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}