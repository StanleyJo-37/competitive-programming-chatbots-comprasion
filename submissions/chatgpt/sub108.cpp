#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        long long k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Map to count how many times each power of k is used across all a[i]
        map<long long, int> power_count;

        bool possible = true;
        for (int i = 0; i < n; ++i) {
            long long x = a[i];
            long long power = 0;
            // Decompose a[i] into base-k representation
            while (x > 0) {
                long long rem = x % k;
                // If any digit in base-k is more than 1, it's impossible
                if (rem > 1) {
                    possible = false;
                    break;
                }
                if (rem == 1) {
                    // If this power of k is already used by another a[j], impossible
                    if (power_count[power]) {
                        possible = false;
                        break;
                    }
                    power_count[power] = 1;
                }
                x /= k;
                ++power;
            }
            if (!possible) break;
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
    return 0;
}