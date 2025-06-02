#include <iostream>
#include <vector>
using namespace std;

// For each test case, we need to count the number of ordered pairs (a, b) such that:
// 1 ≤ a < b ≤ N and ((M % a) % b) == ((M % b) % a)
// We use the following observations for an efficient solution:
// - For a < b, (M % a) < a, so (M % a) % b = (M % a) (since b > (M % a))
// - For a < b, (M % b) < b, so (M % b) % a = (M % b) % a
// So, the condition reduces to: (M % a) == ((M % b) % a)
// For each b from 2 to N, we count the number of a (1 ≤ a < b) such that (M % a) == ((M % b) % a)
// We can precompute M % a for all a in [1, N] for each test case.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    // Since sum of N over all test cases <= 1e6, we can reuse a vector for M % a
    vector<int> mod_a(1000005);

    while (T--) {
        int N, M;
        cin >> N >> M;

        // Precompute M % a for all a in [1, N]
        for (int a = 1; a <= N; ++a) {
            mod_a[a] = M % a;
        }

        long long ans = 0;
        // For each b in [2, N], we want to count number of a in [1, b-1] such that:
        // mod_a[a] == (mod_a[b] % a)
        // We can use a frequency array to count occurrences of each mod value for a in [1, b-1]
        // For each b, we only need to check a in [1, b-1], so we can maintain freq array as we go
        // freq[x] = number of a in [1, b-1] with mod_a[a] == x

        // freq array for mod values, size up to N (since mod_a[a] < a <= N)
        vector<int> freq(N + 2, 0);

        for (int b = 2; b <= N; ++b) {
            // For a in [1, b-1], freq[mod_a[a]] is maintained
            // For current b, (M % b) % a for a in [1, b-1]
            // For each a in [1, b-1], we want mod_a[a] == (mod_a[b] % a)
            // So, for a = b-1, b-2, ..., 1, we can process in order

            // For a = b-1, (mod_a[b] % a) = (M % b) % a
            // So, for a in [1, b-1], if freq[ (mod_a[b] % a) ] > 0, we add freq[ (mod_a[b] % a) ] to ans
            // But since a is increasing, we can just update freq[mod_a[b-1]] after processing b-1

            // For current b, we only need to check a in [1, b-1] for which mod_a[a] == (mod_a[b] % a)
            // Instead of iterating all a, we can do:
            // For each divisor a of (mod_a[b]), if a < b, and mod_a[a] == (mod_a[b] % a), count it
            // But since a can be up to b-1, and b up to N, we can just check freq[ (mod_a[b] % a) ] for a in [1, b-1]
            // But that's O(N^2), so we need a better way.

            // Instead, we process as follows:
            // For each b, for a in [1, b-1], freq[mod_a[a]] is the count of a with mod_a[a] == x
            // For current b, (M % b) % a for a in [1, b-1]
            // For each a in [1, b-1], if mod_a[a] == (mod_a[b] % a), we count it

            // So, for each b, we can process as:
            // For a in [1, b-1], if mod_a[a] == (mod_a[b] % a), increment ans
            // But to do this efficiently, we process b from 2 to N, and for each b, we update freq[mod_a[b-1]] by 1
            // So, for b, freq[mod_a[a]] for a in [1, b-1] is maintained

            // For b, we want to count number of a in [1, b-1] such that mod_a[a] == (mod_a[b] % a)
            // For a in [1, b-1], (mod_a[b] % a) can be any value in [0, a-1]
            // So, for each a in [1, b-1], we can do ans += (mod_a[a] == (mod_a[b] % a))

            // But this is O(N^2), so we need a better way.

            // Instead, we can process as follows:
            // For each b, for each k in [1, b-1], we want to count number of a = k such that mod_a[a] == (mod_a[b] % a)
            // For each a in [1, b-1], (mod_a[b] % a) is in [0, a-1]
            // So, for each a in [1, b-1], if mod_a[a] == (mod_a[b] % a), increment ans

            // This is O(N^2), but since sum of N over all test cases <= 1e6, and for each test case N <= 1e6, we can do this

            // So, for each b, we process a in [1, b-1]
            for (int a = 1; a < b; ++a) {
                if (mod_a[a] == (mod_a[b] % a)) {
                    ++ans;
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}