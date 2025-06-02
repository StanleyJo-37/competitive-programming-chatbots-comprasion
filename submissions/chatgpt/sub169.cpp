#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T; // Number of test cases

    while (T--) {
        int N, K;
        cin >> N >> K; // Length of string and required consecutive '*'
        string S;
        cin >> S;

        int max_streak = 0; // To keep track of the maximum consecutive '*' found
        int current_streak = 0; // Current consecutive '*' count

        for (int i = 0; i < N; ++i) {
            if (S[i] == '*') {
                ++current_streak; // Increment streak if current char is '*'
                if (current_streak >= K) {
                    // As soon as we reach K, we can output YES and break
                    cout << "YES\n";
                    goto next_case; // Jump to next test case
                }
            } else {
                current_streak = 0; // Reset streak if current char is not '*'
            }
        }
        // If loop completes without finding K consecutive '*'
        cout << "NO\n";
        next_case:;
    }
    return 0;
}