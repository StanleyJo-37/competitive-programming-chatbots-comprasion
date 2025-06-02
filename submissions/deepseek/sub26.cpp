#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    const int MAX_A = 1e6 + 5;
    vector<int> dp(MAX_A, 0);

    // Precompute frequency of each number in the array
    vector<int> freq(MAX_A, 0);
    for (int num : a) {
        freq[num] = 1;
    }

    // Dynamic programming approach to find the longest divisible chain
    int max_clique = 0;
    for (int i = 1; i < MAX_A; ++i) {
        if (freq[i]) {
            dp[i] = max(dp[i], 1);
            for (int j = 2 * i; j < MAX_A; j += i) {
                if (freq[j]) {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
            max_clique = max(max_clique, dp[i]);
        }
    }

    cout << max_clique << '\n';
    return 0;
}