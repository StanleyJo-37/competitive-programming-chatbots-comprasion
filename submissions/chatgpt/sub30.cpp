#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input values: n = number of rangers, k = number of operations, x = Jon's favourite number
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // If k == 0, no operation is performed, so just output max and min
    if (k == 0) {
        int mx = *max_element(a.begin(), a.end());
        int mn = *min_element(a.begin(), a.end());
        cout << mx << " " << mn << "\n";
        return 0;
    }

    // Since the range of strengths and x is small (<= 1000), we can use a frequency array
    // freq[i] = number of rangers with strength i
    const int MAX_A = 1024; // since 0 <= a_i, x <= 1000, 1024 is enough
    vector<long long> freq(MAX_A, 0);
    for (int i = 0; i < n; ++i) freq[a[i]]++;

    // To detect cycles, we can use a map to store the state of freq after each operation
    // If a state repeats, we can stop early
    map<vector<long long>, int> seen;

    for (int step = 0; step < k; ++step) {
        // If this state has been seen before, we are in a cycle, so break
        if (seen.count(freq)) break;
        seen[freq] = step;

        // Prepare a new frequency array for the next state
        vector<long long> new_freq(MAX_A, 0);

        // cnt is the number of rangers processed so far (to determine alternate positions)
        long long cnt = 0;
        for (int i = 0; i < MAX_A; ++i) {
            if (freq[i] == 0) continue;
            // For freq[i] rangers with strength i, we need to split them into two groups:
            // - those to be XORed (at alternate positions starting from the first)
            // - those to remain the same
            long long to_xor = freq[i] / 2;
            long long to_keep = freq[i] / 2;
            // If cnt is even, the first ranger at this strength is at an even position (0-based), so XOR
            // If cnt is odd, the first ranger is at an odd position, so keep
            if (cnt % 2 == 0) {
                // If odd number, one more goes to XOR
                if (freq[i] % 2 == 1) to_xor++;
            } else {
                // If odd number, one more goes to keep
                if (freq[i] % 2 == 1) to_keep++;
            }
            // Update new frequencies
            new_freq[i ^ x] += to_xor;
            new_freq[i] += to_keep;
            cnt += freq[i];
        }
        freq = new_freq;
    }

    // After all operations, find the minimum and maximum strength with non-zero frequency
    int mn = -1, mx = -1;
    for (int i = 0; i < MAX_A; ++i) {
        if (freq[i] > 0) {
            if (mn == -1) mn = i;
            mx = i;
        }
    }
    cout << mx << " " << mn << "\n";
    return 0;
}