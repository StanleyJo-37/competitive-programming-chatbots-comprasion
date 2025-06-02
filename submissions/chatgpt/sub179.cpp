#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;

        // flip_diff[i]: number of flips starting at position i
        // We use a difference array to efficiently apply range flips
        vector<int> flip_diff(N + 2, 0);

        int flip = 0; // current number of flips affecting position i
        for (int i = 0; i <= N - K; ++i) {
            // Update current flip count
            flip += flip_diff[i];

            // If after current flips, S[i] is '1', we want to flip it to '0'
            // So, if (S[i] - '0' + flip) % 2 == 1, then S[i] is '1' after flips
            if (((S[i] - '0') + flip) % 2 == 1) {
                // Flip at position i
                flip += 1;
                flip_diff[i] += 1;
                flip_diff[i + K] -= 1; // Remove effect after K positions
            }
        }

        // Now, process the rest of the string (positions N-K+1 to N-1)
        for (int i = N - K + 1; i < N; ++i) {
            flip += flip_diff[i];
            // For these positions, we cannot flip anymore, just apply the current flip count
            // If after flips, S[i] is '1', it remains '1'
        }

        // Build the final string
        string res = S;
        flip = 0;
        for (int i = 0; i < N; ++i) {
            flip += flip_diff[i];
            // If flip is even, character stays the same; if odd, it is flipped
            if (flip % 2 == 0) {
                res[i] = S[i];
            } else {
                res[i] = (S[i] == '0' ? '1' : '0');
            }
        }

        cout << res << '\n';
    }
    return 0;
}