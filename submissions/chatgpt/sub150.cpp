#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// This function checks if it's possible to arrange the array such that
// the maximum XOR between adjacent elements is <= 'limit'.
// It uses a greedy approach: always connect the closest available number
// (in sorted order) to minimize the XOR.
bool isPossible(const vector<int>& a, int limit) {
    int n = a.size();
    vector<bool> used(n, false);
    // Try all possible starting points (since the permutation can start anywhere)
    for (int start = 0; start < n; ++start) {
        fill(used.begin(), used.end(), false);
        used[start] = true;
        int last = start;
        bool ok = true;
        for (int cnt = 1; cnt < n; ++cnt) {
            bool found = false;
            // Try to find the next unused element with XOR <= limit
            for (int j = 0; j < n; ++j) {
                if (!used[j] && (a[last] ^ a[j]) <= limit) {
                    used[j] = true;
                    last = j;
                    found = true;
                    break;
                }
            }
            if (!found) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Sort the array to make greedy connections easier
    sort(a.begin(), a.end());

    // Binary search for the minimal possible score
    int left = 0, right = (1 << 30), answer = right;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // If possible to arrange with max XOR <= mid, try smaller
        if (isPossible(a, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << answer << endl;
    return 0;
}