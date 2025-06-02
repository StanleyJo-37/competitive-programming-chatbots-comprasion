#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    string a, b;
    cin >> a >> b;
    
    // Sort both strings to pick the smallest characters greedily
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    string c;
    int i = 0, j = 0;
    int consecutive_a = 0, consecutive_b = 0;
    
    while (i < n && j < m) {
        // Decide whether to pick from a or b
        bool pick_a = false;
        if (consecutive_a < k) {
            if (consecutive_b < k) {
                // Pick the smaller character
                pick_a = a[i] < b[j];
            } else {
                // Must pick from a to avoid exceeding k consecutive from b
                pick_a = true;
            }
        } else {
            // Must pick from b to avoid exceeding k consecutive from a
            pick_a = false;
        }
        
        if (pick_a) {
            c += a[i++];
            consecutive_a++;
            consecutive_b = 0;
        } else {
            c += b[j++];
            consecutive_b++;
            consecutive_a = 0;
        }
    }
    
    // Append remaining characters from a or b
    while (i < n) {
        c += a[i++];
    }
    while (j < m) {
        c += b[j++];
    }
    
    cout << c << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}