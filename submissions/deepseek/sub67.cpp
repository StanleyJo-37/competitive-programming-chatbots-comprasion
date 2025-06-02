#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> codes(n);
    for (int i = 0; i < n; ++i) {
        cin >> codes[i];
    }

    int max_k = INT_MAX;

    // For each promocode, find the minimal number of differing digits with any other promocode.
    // The maximum k is the minimal such value minus 1 (since k must allow unique identification).
    for (int i = 0; i < n; ++i) {
        int min_diff = 6; // Maximum possible difference for 6-digit codes.
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int diff = 0;
            for (int k = 0; k < 6; ++k) {
                if (codes[i][k] != codes[j][k]) {
                    diff++;
                }
            }
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        // The maximum k for this promocode is (min_diff - 1) / 2, but since errors can be in any digits,
        // the correct k is floor((min_diff - 1)/2). However, the problem requires that any promocode
        // can be uniquely identified with at most k errors, so the global k is the minimal (min_diff - 1)/2.
        // But the actual condition is that the minimal distance between any two codes must be at least 2k+1.
        // Therefore, the maximum k is floor((min_diff - 1)/2) for the minimal min_diff among all codes.
        if (min_diff - 1 < max_k) {
            max_k = min_diff - 1;
        }
    }

    // The maximum k is the floor of (global_min_diff - 1) / 2.
    // But since the problem requires that any code can be uniquely identified with at most k errors,
    // the minimal distance between any two codes must be at least 2k + 1.
    // Therefore, the maximum possible k is (global_min_diff - 1) / 2.
    // However, since the minimal min_diff is the minimal distance between any two codes,
    // the maximum k is (min_diff - 1) / 2.
    // But in the first loop, we stored (min_diff - 1) in max_k, so we need to divide by 2.
    max_k = max_k / 2;

    // Edge case: if all codes are the same (but problem states all are distinct), but n=1, then k=6.
    if (n == 1) {
        max_k = 6;
    }

    cout << max_k << endl;

    return 0;
}