#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        
        bool possible = true;
        // The total length of a1..a_{k+1} and R(a1)..R(a_k) must be n.
        // The structure is a1..a_{k+1}..R(a_k)..R(a1).
        // So, for the string to satisfy the condition, the first k and last k characters must mirror each other.
        // We need to check if the first k characters match the reverse of the last k characters.
        // The middle part (a_{k+1}) can be anything, but must exist (non-empty).
        for (int i = 0; i < k; ++i) {
            if (s[i] != s[n - 1 - i]) {
                possible = false;
                break;
            }
        }
        // Additionally, after checking the k pairs, there must be at least one character left for a_{k+1}.
        // So, n must be >= 2*k + 1 (since a_{k+1} must be non-empty).
        if (possible && n >= 2 * k + 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}