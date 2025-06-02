#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    stack<int> st;
    int max_xor = 0;

    // Process each element to find the maximum XOR between any element and the next greater element (left or right)
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top() < s[i]) {
            max_xor = max(max_xor, st.top() ^ s[i]);
            st.pop();
        }
        if (!st.empty()) {
            max_xor = max(max_xor, st.top() ^ s[i]);
        }
        st.push(s[i]);
    }

    cout << max_xor << endl;
    return 0;
}