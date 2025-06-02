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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        
        // The maximum operations is n if all elements are distinct.
        // If there are duplicates, the minimal operations is n - (min_freq - 1),
        // where min_freq is the minimal frequency of any element.
        // However, if the minimal frequency is 1, then it's still n.
        // So, the answer is n if all elements are unique, else n - (min_freq - 1).
        // But in the case where min_freq is 2, the answer is n - 1.
        // For example, in the second test case, min_freq is 2, so 4 - (2-1) = 3.
        
        // Find the frequency of each element.
        vector<int> freq(n + 1, 0);
        for (int num : a) {
            freq[num]++;
        }
        
        int min_freq = *min_element(freq.begin() + 1, freq.end());
        
        if (min_freq == 1) {
            cout << n << endl;
        } else if (min_freq == 2) {
            cout << n - 1 << endl;
        } else {
            // For min_freq >= 3, the answer is n - (min_freq - 1).
            // But in reality, the minimal case is when min_freq is 2.
            // So, the answer is n - (min_freq - 1).
            cout << n - (min_freq - 1) << endl;
        }
    }
    return 0;
}