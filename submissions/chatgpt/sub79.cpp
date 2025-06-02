#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

// Function to check if s can be transformed to t by swapping exactly two characters
bool can_obtain_by_one_swap(const string& s, const string& t) {
    int n = s.size();
    vector<int> diff;
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) diff.push_back(i);
    }
    // If no difference, we need at least one duplicate character to swap
    if (diff.empty()) {
        set<char> st(s.begin(), s.end());
        return st.size() < n;
    }
    // If exactly two differences, check if swapping them makes strings equal
    if (diff.size() == 2) {
        int i = diff[0], j = diff[1];
        return s[i] == t[j] && s[j] == t[i];
    }
    // Otherwise, not possible
    return false;
}

int main() {
    int k, n;
    cin >> k >> n;
    vector<string> a(k);
    for (int i = 0; i < k; ++i) cin >> a[i];

    // Try all possible pairs of positions to swap in the first string
    string base = a[0];
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            string candidate = base;
            swap(candidate[i], candidate[j]);
            bool ok = true;
            for (int t = 0; t < k; ++t) {
                if (!can_obtain_by_one_swap(candidate, a[t])) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << candidate << endl;
                return 0;
            }
        }
    }
    // If no valid string found, output -1
    cout << -1 << endl;
    return 0;
}