#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string a, b;
    cin >> n >> a >> b;
    
    vector<int> operations;
    bool flipped = false;
    int left = 0, right = n - 1;
    
    for (int i = n - 1; i >= 0; --i) {
        // Determine the current effective character at the right boundary
        char current_a = a[right];
        if (flipped) {
            current_a = (current_a == '0' ? '1' : '0');
        }
        
        if (current_a == b[i]) {
            // No operation needed for this position
            if (left <= right) {
                if (flipped) left++;
                else right--;
            }
            continue;
        }
        
        // Check the first character (left boundary)
        char first_a = a[left];
        if (flipped) {
            first_a = (first_a == '0' ? '1' : '0');
        }
        
        if (first_a == b[i]) {
            // Flip the first character alone (prefix of length 1)
            operations.push_back(1);
        }
        
        // Flip the prefix of length (i + 1)
        operations.push_back(i + 1);
        flipped = !flipped;
        swap(left, right);
        
        // Adjust the boundaries based on the flip direction
        if (flipped) left++;
        else right--;
    }
    
    cout << operations.size() << " ";
    for (int op : operations) {
        cout << op << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}