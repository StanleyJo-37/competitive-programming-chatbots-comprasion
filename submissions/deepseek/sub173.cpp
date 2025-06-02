#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int N = S.size();
        vector<int> zerosAfter(N + 1, 0); // zerosAfter[i] = number of '0's after the i-th position (1-based)
        
        // Precompute the number of zeros after each position
        for (int i = N - 1; i >= 0; --i) {
            zerosAfter[i] = zerosAfter[i + 1] + (S[i] == '0' ? 1 : 0);
        }

        long long totalTime = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '1') {
                int availableZeros = zerosAfter[i];
                if (availableZeros > 0) {
                    // Each '1' at position i can contribute (1 + availableZeros) seconds
                    // 1 second to choose, and availableZeros seconds to move
                    totalTime += 1 + availableZeros;
                }
            }
        }
        cout << totalTime << '\n';
    }
    return 0;
}