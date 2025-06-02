#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

// Precompute all powerful numbers (powers of two and factorials) up to 1e12
vector<long long> get_powerful_numbers() {
    set<long long> s;

    // Add all powers of two up to 1e12
    for (int d = 0; ; ++d) {
        long long val = 1LL << d;
        if (val > 1e12) break;
        s.insert(val);
    }

    // Add all factorials up to 1e12
    long long fact = 1;
    for (int d = 0; ; ++d) {
        if (fact > 1e12) break;
        s.insert(fact);
        if (d == 0) fact = 1;
        else fact *= d;
        if (fact > 1e12) break;
    }

    // Convert set to vector and sort in descending order for greedy
    vector<long long> powerful(s.begin(), s.end());
    sort(powerful.rbegin(), powerful.rend());
    return powerful;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute all powerful numbers
    vector<long long> powerful = get_powerful_numbers();
    int sz = powerful.size();

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;

        int answer = INT_MAX;

        // For small n, try all subsets of factorials (since their count is small)
        // and fill the rest with powers of two (which is like binary representation)
        // First, collect all factorials (excluding 1, since 1 is both a power of two and a factorial)
        vector<long long> factorials;
        long long fact = 1;
        for (int d = 0; ; ++d) {
            if (fact > n) break;
            factorials.push_back(fact);
            if (d == 0) fact = 1;
            else fact *= d;
            if (fact > n) break;
        }
        int fsz = factorials.size();

        // For all subsets of factorials (up to 2^fsz, fsz <= 20)
        // For each subset, sum the factorials, and try to fill the rest with powers of two
        // (powers of two are always distinct, so we can use binary representation)
        for (int mask = 0; mask < (1 << fsz); ++mask) {
            long long sum = 0;
            int cnt = 0;
            for (int i = 0; i < fsz; ++i) {
                if (mask & (1 << i)) {
                    sum += factorials[i];
                    ++cnt;
                }
            }
            if (sum > n) continue;
            long long rem = n - sum;
            // If rem can be represented as sum of distinct powers of two (i.e., no overlap with used factorials that are also powers of two)
            // We need to make sure that we don't use the same number twice (e.g., 1! and 2^0 both are 1)
            // So, for each factorial used, if it is also a power of two, we must not use it again in the binary representation
            // So, for the set of factorials used, collect which ones are powers of two
            set<long long> used;
            for (int i = 0; i < fsz; ++i) {
                if (mask & (1 << i)) {
                    used.insert(factorials[i]);
                }
            }
            // Now, for rem, count the number of set bits, but skip the bits corresponding to used powers of two
            int add = 0;
            bool valid = true;
            for (int bit = 0; (1LL << bit) <= rem; ++bit) {
                if (rem & (1LL << bit)) {
                    long long val = 1LL << bit;
                    if (used.count(val)) {
                        valid = false;
                        break;
                    }
                    ++add;
                }
            }
            if (valid) {
                answer = min(answer, cnt + add);
            }
        }

        // If answer is still INT_MAX, it's not possible
        if (answer == INT_MAX) cout << -1 << '\n';
        else cout << answer << '\n';
    }
    return 0;
}