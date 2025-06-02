#include <iostream>
using namespace std;

// Function to compute the length of the longest subarray
// such that the bitwise AND of all elements is positive.
int longestSubarray(int N) {
    // The answer is the largest power of 2 less than or equal to N
    // For any subarray of length >= k, if it contains both x and x+1, their AND is 0 if x is odd.
    // The only way to have AND > 0 is to take a segment of numbers where the highest bit is the same.
    // That is, the largest segment is of length equal to the highest power of 2 <= N.
    int res = 1;
    while (res * 2 <= N) {
        res *= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << longestSubarray(N) << '\n';
    }
    return 0;
}