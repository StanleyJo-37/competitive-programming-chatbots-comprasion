#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    // The idea is to use a monotonic stack to efficiently find, for each element,
    // the next greater and previous greater elements, and for each such pair,
    // compute the lucky number (max xor second max).
    // For every pair of adjacent elements in the stack, their xor is a candidate.

    int ans = 0;
    stack<int> st; // stack will store the values, not indices

    // Traverse from left to right
    for (int i = 0; i < n; ++i) {
        // While the stack is not empty and the top is less than current element
        while (!st.empty() && st.top() < s[i]) {
            // The pair (s[i], st.top()) is a candidate
            ans = max(ans, s[i] ^ st.top());
            st.pop();
        }
        // If stack is not empty, the pair (st.top(), s[i]) is also a candidate
        if (!st.empty()) {
            ans = max(ans, st.top() ^ s[i]);
        }
        st.push(s[i]);
    }

    // Now traverse from right to left for completeness (to catch all pairs)
    // (Actually, the above is sufficient, but for clarity and completeness, we do both directions)
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && st.top() < s[i]) {
            ans = max(ans, s[i] ^ st.top());
            st.pop();
        }
        if (!st.empty()) {
            ans = max(ans, st.top() ^ s[i]);
        }
        st.push(s[i]);
    }

    cout << ans << endl;
    return 0;
}