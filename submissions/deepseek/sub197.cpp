#include <iostream>
#include <vector>

using namespace std;

vector<int> countingSort(vector<int> arr) {
    // Since the problem constraints specify 0 <= arr[i] < 100,
    // we can initialize a count array of size 100.
    vector<int> count(100, 0);
    
    // Count the occurrences of each number in the input array.
    for (int num : arr) {
        count[num]++;
    }
    
    // Reconstruct the sorted array from the count array.
    vector<int> sorted;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            sorted.push_back(i);
        }
    }
    
    return sorted;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> sorted = countingSort(arr);
    
    for (int i = 0; i < sorted.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << sorted[i];
    }
    
    return 0;
}