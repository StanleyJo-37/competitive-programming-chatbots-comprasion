#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if a number is palindromic in binary
bool is_palindromic(int x) {
    vector<int> bits;
    while (x > 0) {
        bits.push_back(x & 1);
        x >>= 1;
    }
    int l = 0, r = bits.size() - 1;
    while (l < r) {
        if (bits[l] != bits[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    // Precompute all good numbers up to 1000
    vector<int> good;
    for (int i = 1; i <= 1000; ++i) {
        if (is_palindromic(i)) good.push_back(i);
    }
    // Sort in descending order for greedy approach
    sort(good.rbegin(), good.rend());

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> ans;
        int remain = n;
        // Greedily subtract the largest possible good number
        for (int i = 0; i < good.size() && remain > 0; ++i) {
            while (good[i] <= remain) {
                ans.push_back(good[i]);
                remain -= good[i];
                // Since at most 12 numbers are allowed, break if reached
                if (ans.size() == 12) break;
            }
            if (ans.size() == 12) break;
        }
        // Output the result
        cout << ans.size() << '\n';
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] << (i + 1 == ans.size() ? '\n' : ' ');
        }
    }
    return 0;
}