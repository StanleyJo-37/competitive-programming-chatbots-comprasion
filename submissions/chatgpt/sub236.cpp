#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read number of boys
    int n;
    cin >> n;
    vector<int> boys(n);
    for (int i = 0; i < n; ++i) {
        cin >> boys[i];
    }

    // Read number of girls
    int m;
    cin >> m;
    vector<int> girls(m);
    for (int i = 0; i < m; ++i) {
        cin >> girls[i];
    }

    // Sort both boys' and girls' skill levels to use two pointers efficiently
    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    int i = 0, j = 0, pairs = 0;
    // Use two pointers to find the maximum number of valid pairs
    while (i < n && j < m) {
        // If the skill difference is at most 1, form a pair
        if (abs(boys[i] - girls[j]) <= 1) {
            ++pairs;
            ++i;
            ++j;
        }
        // If the current boy's skill is less, move to the next boy
        else if (boys[i] < girls[j]) {
            ++i;
        }
        // If the current girl's skill is less, move to the next girl
        else {
            ++j;
        }
    }

    // Output the maximum number of pairs
    cout << pairs << endl;
    return 0;
}