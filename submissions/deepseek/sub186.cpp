#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int n = S.size();

        // The minimal swaps to unbalance can be either:
        // 1. Make the first two characters "))" (swap first ')' leftwards)
        // 2. Make the last two characters "((" (swap last '(' rightwards)
        // The answer is the minimum of these two options.

        // Option 1: Find the first ')', swap it left to position 1 (0-based index 1)
        // The number of swaps is the index of the first ')'
        int first_close = -1;
        for (int i = 0; i < n; ++i) {
            if (S[i] == ')') {
                first_close = i;
                break;
            }
        }
        int option1 = first_close;

        // Option 2: Find the last '(', swap it right to position n-2 (0-based index n-2)
        // The number of swaps is (n - 1 - last_open)
        int last_open = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (S[i] == '(') {
                last_open = i;
                break;
            }
        }
        int option2 = (n - 1) - last_open;

        // The answer is the minimum of the two options
        cout << min(option1, option2) << '\n';
    }

    return 0;
}