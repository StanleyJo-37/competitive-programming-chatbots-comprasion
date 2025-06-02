#include <iostream>
#include <vector>
using namespace std;

// Function to find the deleted number from the sequence
int findDeletedNumber(const vector<int>& arr, int N) {
    // Calculate the expected sum of numbers from 1 to N
    long long expectedSum = (long long)N * (N + 1) / 2;
    // Calculate the actual sum of the given array
    long long actualSum = 0;
    for (int num : arr) {
        actualSum += num;
    }
    // The deleted number is the difference between expected and actual sum
    int deleted = (int)(expectedSum - actualSum);
    // If no number is deleted, return 0
    if (deleted == 0) return 0;
    // Otherwise, return the deleted number
    return deleted;
}

int main() {
    // Read N (the original length of the sequence)
    int N;
    cin >> N;
    // Read the mixed array with possibly one number deleted
    vector<int> arr;
    for (int i = 0; i < N - 1 && N > 0; ++i) {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    // Output the result
    cout << findDeletedNumber(arr, N) << endl;
    return 0;
}