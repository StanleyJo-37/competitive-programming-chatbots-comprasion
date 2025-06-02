#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> groups(n);
    for (int i = 0; i < n; ++i) {
        cin >> groups[i];
    }
    
    // Sort the groups to easily find the middle element (since n is odd)
    sort(groups.begin(), groups.end());
    
    // The middle element is Igor's entrance year because:
    // - The groups form a contiguous range centered around his year.
    // - For odd n, the middle element is the center of this range.
    cout << groups[n / 2] << endl;
    
    return 0;
}