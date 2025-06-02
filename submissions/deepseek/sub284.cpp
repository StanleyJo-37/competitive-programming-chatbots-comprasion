#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        unordered_set<int> unique_elements;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            unique_elements.insert(a[i]);
        }
        
        // If the number of unique elements is more than k, it's impossible
        if (unique_elements.size() > k) {
            cout << -1 << endl;
            continue;
        }
        
        // Construct the pattern to repeat: all unique elements, then pad with 1s (or any element) to reach size k
        vector<int> pattern;
        for (int num : unique_elements) {
            pattern.push_back(num);
        }
        // Pad the pattern to size k with the first element (or any existing element)
        while (pattern.size() < k) {
            pattern.push_back(*unique_elements.begin());
        }
        
        // The resulting array is the pattern repeated n times (or any m >= n)
        // Since each window of size k will be the pattern, all sums will be equal
        int m = n * k;
        cout << m << endl;
        for (int i = 0; i < m; ++i) {
            cout << pattern[i % k] << " ";
        }
        cout << endl;
    }
}

int main() {
    solve();
    return 0;
}