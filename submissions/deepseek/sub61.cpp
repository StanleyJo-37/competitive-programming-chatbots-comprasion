#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<long long> generate_powerful_numbers() {
    vector<long long> powerful;
    // Generate all factorials <= 1e12
    long long fact = 1;
    for (int d = 1; ; ++d) {
        if (d >= 2) {
            fact *= d;
            if (fact > 1e12) break;
        }
        powerful.push_back(fact);
    }
    // Generate all powers of 2 <= 1e12
    for (int d = 0; ; ++d) {
        long long power = 1LL << d;
        if (power > 1e12) break;
        powerful.push_back(power);
    }
    // Remove duplicates and sort
    sort(powerful.begin(), powerful.end());
    powerful.erase(unique(powerful.begin(), powerful.end()), powerful.end());
    return powerful;
}

int solve(long long n, const vector<long long>& powerful) {
    int min_k = INT_MAX;
    int m = powerful.size();
    // Iterate all possible subsets of factorials (since factorials grow faster, limit to small subsets)
    for (int mask = 0; mask < (1 << 15); ++mask) {
        long long sum = 0;
        int k = 0;
        for (int i = 0; i < 15; ++i) {
            if (mask & (1 << i)) {
                if (i >= powerful.size()) break;
                sum += powerful[i];
                k++;
                if (sum > n) break;
            }
        }
        if (sum > n) continue;
        long long remaining = n - sum;
        // The remaining sum must be formed by distinct powerful numbers not used in the mask
        // Since factorials are already considered in the mask, remaining must be sum of distinct powers of 2
        // The count of set bits in remaining is the minimal number of powers of 2 needed
        int bits = __builtin_popcountll(remaining);
        // Check if all the powerful numbers used in the mask and the powers of 2 are distinct
        // Since factorials and powers of 2 are distinct except for 1 and 2 (1! = 1 = 2^0, 2! = 2 = 2^1)
        // So we need to ensure that if 1 or 2 is used in the mask, it's not used again in the remaining
        bool conflict = false;
        for (int i = 0; i < 15; ++i) {
            if (mask & (1 << i)) {
                if (powerful[i] == 1 && (remaining & 1)) {
                    conflict = true;
                    break;
                }
                if (powerful[i] == 2 && (remaining & 2)) {
                    conflict = true;
                    break;
                }
            }
        }
        if (!conflict) {
            min_k = min(min_k, k + bits);
        }
    }
    return (min_k == INT_MAX) ? -1 : min_k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<long long> powerful = generate_powerful_numbers();
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << solve(n, powerful) << '\n';
    }
    return 0;
}