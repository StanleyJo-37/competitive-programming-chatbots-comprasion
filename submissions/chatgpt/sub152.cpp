#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        // Compute prefix XORs: prefixXor[i] = A[0] ^ ... ^ A[i-1]
        // prefixXor[0] = 0 (empty prefix)
        vector<int> prefixXor(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            prefixXor[i] = prefixXor[i - 1] ^ A[i - 1];
        }

        // We want to count the number of triples (i, j, k) such that:
        // 1 <= i < j <= k <= N
        // A_i ^ ... ^ A_{j-1} == A_j ^ ... ^ A_k
        // Let S = prefixXor
        // A_i ^ ... ^ A_{j-1} = S[j-1] ^ S[i-1]
        // A_j ^ ... ^ A_k = S[k] ^ S[j-1]
        // So, S[j-1] ^ S[i-1] == S[k] ^ S[j-1]
        // => S[i-1] == S[k]
        // For each pair (i-1, k) with S[i-1] == S[k], for all j in (i, k], (i < j <= k), (i < j <= k)
        // For each such (i-1, k), number of j is (k - (i-1) - 1) = (k - i)
        // But since i < j <= k, i in [1, k], j in [i+1, k], so for each (i-1, k) with S[i-1] == S[k], add (k - i) to answer

        // To optimize, for each prefixXor value, keep track of:
        // - count of occurrences (how many times this value has appeared up to current index)
        // - sum of indices where it has appeared (to compute total (k - i) efficiently)
        unordered_map<int, long long> count, sum_indices;
        long long ans = 0;
        for (int idx = 0; idx <= N; ++idx) {
            int val = prefixXor[idx];
            // For all previous occurrences of val at indices i-1, we can form (i, j, k) with i in [1, idx], j in (i, idx], k = idx
            // For each such i-1, add (idx - (i-1) - 1) = (idx - i) to answer
            // The total sum for all previous i-1 is: count[val] * (idx) - sum_indices[val]
            if (count.find(val) != count.end()) {
                ans += count[val] * (idx) - sum_indices[val];
            }
            // Update count and sum_indices for this prefixXor value
            count[val]++;
            sum_indices[val] += idx;
        }
        cout << ans << '\n';
    }
    return 0;
}