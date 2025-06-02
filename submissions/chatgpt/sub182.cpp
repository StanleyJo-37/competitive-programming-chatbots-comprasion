#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

// For each test case, we need to count the number of pairs (i, j) such that
// the substring S[i..j] is "special", i.e., number of 0's = (number of 1's)^2.
// Brute force is not feasible due to constraints, so we use prefix sums and hashing.

// The key observation is that for any substring S[l..r]:
//   cnt1 = prefix1[r+1] - prefix1[l]
//   cnt0 = prefix0[r+1] - prefix0[l]
// We want cnt0 = cnt1^2
// Rearranged: prefix0[r+1] - prefix0[l] = (prefix1[r+1] - prefix1[l])^2
// For fixed r, for all l <= r, we want to count l such that:
//   prefix0[l] = prefix0[r+1] - (prefix1[r+1] - prefix1[l])^2
// But this is not directly hashable, so we use a different approach.

// For each position, we keep prefix sums of 1's and 0's.
// For each possible value of k = cnt1 in substring, we want to find all l such that
//   prefix0[l] = prefix0[r+1] - k^2
//   prefix1[l] = prefix1[r+1] - k
// So, for each r, we try all possible k (number of 1's in substring ending at r).
// Since cnt1 in substring cannot be more than sqrt(n) for small substrings, and for large cnt1, k^2 grows fast.
// So, we only need to try k up to sqrt(2*n) (since k^2 <= n).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int n = S.size();

        // Compute prefix sums for 1's and 0's
        vector<int> prefix1(n + 1, 0), prefix0(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix1[i + 1] = prefix1[i] + (S[i] == '1');
            prefix0[i + 1] = prefix0[i] + (S[i] == '0');
        }

        // For each position, we will use a map to store (prefix1, prefix0) pairs
        // For each r, we try all possible k (number of 1's in substring ending at r)
        // For each k, we want to find l such that:
        //   prefix1[l] = prefix1[r+1] - k
        //   prefix0[l] = prefix0[r+1] - k^2
        // So, for each r, for k = 0 to K, we check if such l exists.

        // To speed up, for each (prefix1, prefix0) pair, we store all positions where it occurs.
        // But since prefix1 and prefix0 are monotonic, we can use a map of maps.

        // For each position, we store the count of (prefix1, prefix0) up to that position.
        unordered_map<long long, unordered_map<long long, int>> count_map;
        // Initialize with (0,0) at position 0
        count_map[0][0] = 1;

        long long ans = 0;
        int max_k = (int)sqrt(2 * n) + 2; // k^2 can be up to n, so k up to sqrt(n)
        for (int r = 1; r <= n; ++r) {
            // For each possible k, check if there is a prefix l such that:
            //   prefix1[l] = prefix1[r] - k
            //   prefix0[l] = prefix0[r] - k^2
            // Try k from 0 up to max_k
            for (int k = 0; k <= max_k; ++k) {
                int need1 = prefix1[r] - k;
                int need0 = prefix0[r] - k * k;
                // If need1 or need0 < 0, break (since prefix sums are non-negative)
                if (need1 < 0 || need0 < 0) break;
                // Add the number of times (need1, need0) has occurred before
                ans += count_map[need1][need0];
            }
            // Update the map with current (prefix1[r], prefix0[r])
            count_map[prefix1[r]][prefix0[r]]++;
        }

        cout << ans << '\n';
    }
    return 0;
}