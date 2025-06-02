#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Precompute the number of "w"s (i.e., "vv" pairs) up to each position from the left
    vector<long long> left_w(n, 0);
    long long v_count = 0;
    for (int i = 0; i < n; ++i) {
        // Count consecutive 'v's
        if (s[i] == 'v') {
            ++v_count;
        } else {
            v_count = 0;
        }
        // Each time we have at least two consecutive 'v's, we have a new "w"
        if (v_count >= 2) {
            left_w[i] = left_w[i-1] + 1;
        } else if (i > 0) {
            left_w[i] = left_w[i-1];
        } else {
            left_w[i] = 0;
        }
    }

    // Precompute the number of "w"s (i.e., "vv" pairs) up to each position from the right
    vector<long long> right_w(n, 0);
    v_count = 0;
    for (int i = n-1; i >= 0; --i) {
        if (s[i] == 'v') {
            ++v_count;
        } else {
            v_count = 0;
        }
        if (v_count >= 2) {
            if (i+1 < n)
                right_w[i] = right_w[i+1] + 1;
            else
                right_w[i] = 1;
        } else if (i+1 < n) {
            right_w[i] = right_w[i+1];
        } else {
            right_w[i] = 0;
        }
    }

    // For each 'o', the number of "wow" subsequences is left_w[i-1] * right_w[i+1]
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'o') {
            long long left = (i > 0) ? left_w[i-1] : 0;
            long long right = (i+1 < n) ? right_w[i+1] : 0;
            result += left * right;
        }
    }

    cout << result << endl;
    return 0;
}