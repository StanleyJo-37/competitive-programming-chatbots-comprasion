#include <iostream>
#include <vector>
using namespace std;

// Function to perform counting sort on the input array
vector<int> countingSort(const vector<int>& arr) {
    // Since arr[i] is in [0, 99], we need a count array of size 100
    const int MAX_VALUE = 100;
    vector<int> count(MAX_VALUE, 0);

    // Count the occurrences of each value in arr
    for (int num : arr) {
        count[num]++;
    }

    // Prepare the sorted result
    vector<int> sorted;
    sorted.reserve(arr.size()); // Reserve space for efficiency

    // For each possible value, append it count[value] times to the result
    for (int value = 0; value < MAX_VALUE; ++value) {
        for (int c = 0; c < count[value]; ++c) {
            sorted.push_back(value);
        }
    }
    return sorted;
}

int main() {
    int n;
    cin >> n; // Read the number of elements

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i]; // Read each element
    }

    // Get the sorted array using counting sort
    vector<int> sorted = countingSort(arr);

    // Print the sorted array as space-separated integers
    for (int i = 0; i < sorted.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << sorted[i];
    }
    cout << endl;

    return 0;
}