#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if a number contains digit d
bool isLucky(int num, int d) {
    while (num > 0) {
        if (num % 10 == d) return true;
        num /= 10;
    }
    return false;
}

// Precompute for numbers up to 200 (since beyond that, any number can be formed by adding 10*d + k)
void precomputeDP(vector<bool>& dp, int d) {
    dp[0] = true;
    for (int i = 1; i <= 200; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (isLucky(j, d) && dp[i - j]) {
                dp[i] = true;
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int q, d;
        cin >> q >> d;
        vector<int> queries(q);
        for (int i = 0; i < q; ++i) {
            cin >> queries[i];
        }

        vector<bool> dp(201, false);
        precomputeDP(dp, d);

        for (int num : queries) {
            bool possible = false;
            if (num >= 200) {
                // For large numbers, subtract multiples of 10*d and check remainder
                // Since 10*d + k can cover any remainder when num is large enough
                possible = true;
            } else {
                possible = dp[num];
            }
            cout << (possible ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}