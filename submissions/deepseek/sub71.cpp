#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to generate all possible subset sums modulo m for a given array segment
void generateSubsetSums(const vector<int>& arr, int start, int end, vector<int>& sums, int m) {
    int n = end - start + 1;
    sums.push_back(0); // Start with the empty subset sum (0)
    for (int i = start; i <= end; ++i) {
        int currentSize = sums.size();
        for (int j = 0; j < currentSize; ++j) {
            int newSum = (sums[j] + arr[i]) % m;
            sums.push_back(newSum);
        }
    }
    // Remove duplicates and sort for binary search
    sort(sums.begin(), sums.end());
    sums.erase(unique(sums.begin(), sums.end()), sums.end());
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m; // Pre-modulo to simplify later calculations
    }

    // Split the array into two halves for meet-in-the-middle
    int mid = n / 2;
    vector<int> leftSums, rightSums;
    generateSubsetSums(a, 0, mid - 1, leftSums, m);
    generateSubsetSums(a, mid, n - 1, rightSums, m);

    int maxSum = 0;
    // For each sum in leftSums, find the best complement in rightSums
    for (int sum : leftSums) {
        // Find the largest rightSum such that sum + rightSum < m
        int complement = m - 1 - sum;
        auto it = upper_bound(rightSums.begin(), rightSums.end(), complement);
        if (it != rightSums.begin()) {
            --it;
            int currentMax = sum + *it;
            if (currentMax > maxSum) {
                maxSum = currentMax;
            }
        }
        // Also check the case where sum + rightSum >= m (modulo wrap-around)
        if (!rightSums.empty()) {
            int currentMax = (sum + rightSums.back()) % m;
            if (currentMax > maxSum) {
                maxSum = currentMax;
            }
        }
    }

    cout << maxSum << endl;
    return 0;
}