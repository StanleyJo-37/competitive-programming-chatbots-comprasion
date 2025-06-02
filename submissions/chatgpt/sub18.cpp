#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int m, s;
    cin >> m >> s;

    // If sum is 0 and length is 1, the only number is 0
    if (s == 0) {
        if (m == 1) {
            cout << "0 0" << endl;
        } else {
            // Otherwise, it's impossible to have a number with leading zeros
            cout << "-1 -1" << endl;
        }
        return 0;
    }

    // If the sum is too large to be represented with m digits (each digit max 9)
    if (s > 9 * m) {
        cout << "-1 -1" << endl;
        return 0;
    }

    // Find the smallest number
    vector<int> min_num(m, 0);
    int sum = s;
    // Fill from the last digit to the first to ensure smallest lexicographically
    for (int i = m - 1; i >= 0; --i) {
        // For the first digit, we must leave at least 1 if it's the most significant digit
        int d = max(0, sum - 9 * i);
        if (i == 0 && d == 0 && sum > 0) d = 1;
        min_num[i] = d;
        sum -= d;
    }

    // If after filling, the sum is not zero, it's impossible
    if (sum != 0) {
        cout << "-1 -1" << endl;
        return 0;
    }

    // Find the largest number
    vector<int> max_num(m, 0);
    sum = s;
    // Fill from the first digit to the last to ensure largest lexicographically
    for (int i = 0; i < m; ++i) {
        int d = min(9, sum);
        max_num[i] = d;
        sum -= d;
    }

    // Output the results
    for (int i = 0; i < m; ++i) cout << min_num[i];
    cout << " ";
    for (int i = 0; i < m; ++i) cout << max_num[i];
    cout << endl;

    return 0;
}