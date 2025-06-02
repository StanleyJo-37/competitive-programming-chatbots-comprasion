#include <iostream>
#include <vector>
using namespace std;

// Function to find the lowest index N where the sum of the left side equals the sum of the right side
int findEvenIndex(const vector<int>& arr) {
    int totalSum = 0;
    // Calculate the total sum of the array
    for (int num : arr) {
        totalSum += num;
    }
    int leftSum = 0;
    // Iterate through the array to find the required index
    for (int i = 0; i < arr.size(); ++i) {
        // rightSum is totalSum minus leftSum minus current element
        int rightSum = totalSum - leftSum - arr[i];
        // If leftSum equals rightSum, return current index
        if (leftSum == rightSum) {
            return i;
        }
        // Add current element to leftSum for next iteration
        leftSum += arr[i];
    }
    // If no such index is found, return -1
    return -1;
}

// Main function to test the implementation
int main() {
    // Test cases as described in the problem statement
    vector<vector<int>> testCases = {
        {1,2,3,4,3,2,1},
        {1,100,50,-51,1,1},
        {20,10,-80,10,10,15,35},
        {1,2,3,4,5,6}, // No such index, should return -1
        {10,-80,10,10,15,35,20}, // No such index, should return -1
        {0,0,0,0,0}, // All zeros, should return 0
        {1}, // Single element, should return 0
        {} // Empty array, should return -1
    };

    for (const auto& arr : testCases) {
        cout << findEvenIndex(arr) << endl;
    }
    return 0;
}