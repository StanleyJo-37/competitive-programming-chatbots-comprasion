#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n; // Read the number of groups Igor joined
    vector<int> years(n);
    for (int i = 0; i < n; ++i) {
        cin >> years[i]; // Read the years of the groups
    }
    // Sort the years to find the median easily
    sort(years.begin(), years.end());
    // Since n is always odd, the median is at index n/2
    cout << years[n/2] << endl;
    return 0;
}