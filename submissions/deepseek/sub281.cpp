#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        string S;
        cin >> S;

        stack<int> st;
        vector<bool> keep(N, false);

        // First pass: Match as many valid pairs as possible
        for (int i = 0; i < N; ++i) {
            if (S[i] == '(') {
                st.push(i);
            } else {
                if (!st.empty()) {
                    keep[st.top()] = true;
                    keep[i] = true;
                    st.pop();
                }
            }
        }

        // Second pass: Count the longest nested structure
        int max_depth = 0;
        int current_depth = 0;
        for (int i = 0; i < N; ++i) {
            if (!keep[i]) continue;
            if (S[i] == '(') {
                current_depth++;
                max_depth = max(max_depth, current_depth);
            } else {
                current_depth--;
            }
        }

        // The minimal dense sequence is a single pair of parentheses at max_depth
        // So the total kept is 2 * max_depth, and the answer is N - 2 * max_depth
        cout << (N - 2 * max_depth) << '\n';
    }

    return 0;
}