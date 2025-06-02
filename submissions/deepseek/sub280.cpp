#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        unordered_map<int, int> freq;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            freq[A[i]]++;
        }

        int max_freq = 0;
        for (auto& p : freq) {
            max_freq = max(max_freq, p.second);
        }

        // If the max frequency is 1, no operation can reduce it further.
        if (max_freq == 1) {
            cout << "1\n";
            continue;
        }

        // Check if there exists another element with frequency == max_freq.
        // If yes, the best we can do is max_freq (since replacing one won't help).
        // Else, the best we can do is max(max_freq - 1, (max_freq + 1) / 2).
        int count_max = 0;
        for (auto& p : freq) {
            if (p.second == max_freq) {
                count_max++;
            }
        }

        if (count_max >= 2) {
            cout << max_freq << "\n";
        } else {
            // The optimal is to split the max_freq into two parts.
            // For example, if max_freq is 5, best is 3 (ceil(5/2)).
            // If max_freq is 4, best is 2 (4/2).
            cout << max((max_freq + 1) / 2, (count_max == 1 && freq.size() > 1) ? max_freq - 1 : 1) << "\n";
        }
    }
    return 0;
}