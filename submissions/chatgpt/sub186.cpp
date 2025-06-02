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
        string S;
        cin >> S;
        int n = S.size();

        // The minimum number of adjacent swaps to make a balanced parenthesis sequence unbalanced
        // is always the minimum number of swaps needed to bring a ')' before a '('.
        // Since the sequence is balanced, all '(' are before their matching ')'.
        // The minimal swap is to bring the first ')' to the front or the last '(' to the end.

        // Find the position of the first ')'
        int first_close = -1;
        for (int i = 0; i < n; ++i) {
            if (S[i] == ')') {
                first_close = i;
                break;
            }
        }

        // Find the position of the last '('
        int last_open = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (S[i] == '(') {
                last_open = i;
                break;
            }
        }

        // To make the sequence unbalanced, we can:
        // 1. Move the first ')' to the front (requires first_close swaps)
        // 2. Move the last '(' to the end (requires n - 1 - last_open swaps)
        // The answer is the minimum of these two
        int ans = min(first_close, n - 1 - last_open);

        // Output the answer for this test case
        cout << ans << '\n';
    }
    return 0;
}