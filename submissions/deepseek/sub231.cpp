#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> original(n), sorted(n);
    for (int i = 0; i < n; ++i) {
        cin >> original[i];
        sorted[i] = original[i];
    }
    
    // Sort the original array to find the optimal permutation
    sort(sorted.begin(), sorted.end());
    
    int count = 0;
    int i = 0, j = 0;
    
    // Use two pointers to find how many elements in the sorted array are greater than the original
    while (i < n && j < n) {
        if (sorted[i] > original[j]) {
            ++count;
            ++i;
            ++j;
        } else {
            ++i;
        }
    }
    
    cout << count << endl;
    return 0;
}