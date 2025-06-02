#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n;
    vector<int> boys(n);
    for (int i = 0; i < n; ++i) {
        cin >> boys[i];
    }
    cin >> m;
    vector<int> girls(m);
    for (int i = 0; i < m; ++i) {
        cin >> girls[i];
    }

    // Sort both arrays to use a greedy approach
    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    int pairs = 0;
    int i = 0, j = 0;

    // Two-pointer technique to find maximum pairs
    while (i < n && j < m) {
        if (abs(boys[i] - girls[j]) <= 1) {
            // If skills differ by at most 1, form a pair
            pairs++;
            i++;
            j++;
        } else if (boys[i] < girls[j]) {
            // If boy's skill is too low, move to next boy
            i++;
        } else {
            // If girl's skill is too low, move to next girl
            j++;
        }
    }

    cout << pairs << endl;
    return 0;
}