#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        
        // Sort a in ascending order and b in descending order to ensure sums are unique
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<int>());
        
        // Output the sorted a and b
        for (int num : a) {
            cout << num << " ";
        }
        cout << endl;
        for (int num : b) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}