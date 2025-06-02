#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_A = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<bool> present(MAX_A + 1, false); // To mark which numbers are present in A

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        present[a[i]] = true;
    }

    // dp[x] = size of the largest clique ending at x (i.e., where x is the largest element)
    vector<int> dp(MAX_A + 1, 0);

    int answer = 1;

    // Process numbers in increasing order
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        dp[x] = 1; // At least the clique of size 1 (itself)
        // For all divisors d of x (d < x and d in A), dp[x] = max(dp[x], dp[d] + 1)
        // But since the graph is defined by divisibility, we can also propagate dp[x] to its multiples
        // However, to avoid TLE, we process only the numbers in A

        // For all divisors d of x (d < x)
        for (int d = 1; d * d <= x; ++d) {
            if (x % d == 0) {
                // d is a divisor
                if (d != x && present[d]) {
                    dp[x] = max(dp[x], dp[d] + 1);
                }
                int d2 = x / d;
                if (d2 != d && d2 != x && present[d2]) {
                    dp[x] = max(dp[x], dp[d2] + 1);
                }
            }
        }
        answer = max(answer, dp[x]);
    }

    cout << answer << '\n';
    return 0;
}