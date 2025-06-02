#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, l;
        cin >> n >> l;
        vector<int> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        
        int y = 0;
        // For each bit position from 0 to l-1, determine the majority bit
        for (int bit = 0; bit < l; ++bit) {
            int count = 0;
            for (int num : x) {
                // Check if the current bit is set in the number
                if (num & (1 << bit)) {
                    count++;
                }
            }
            // If majority of numbers have this bit set, set it in y
            if (count > n / 2) {
                y |= (1 << bit);
            }
        }
        cout << y << endl;
    }
    return 0;
}