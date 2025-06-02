#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if a number's binary representation is a palindrome
bool isGood(int x) {
    if (x == 0) return true; // 0 is considered good (binary '0' is palindrome)
    string binary;
    while (x > 0) {
        binary += (x % 2) + '0';
        x /= 2;
    }
    string rev = binary;
    reverse(rev.begin(), rev.end());
    return binary == rev;
}

// Precompute all good numbers up to 1000 (since n <= 1000)
vector<int> precomputeGoodNumbers() {
    vector<int> goodNumbers;
    for (int i = 0; i <= 1000; ++i) {
        if (isGood(i)) {
            goodNumbers.push_back(i);
        }
    }
    return goodNumbers;
}

// Solve for a given n using the precomputed good numbers
vector<int> solve(int n, const vector<int>& goodNumbers) {
    // Try to find a solution with 1 or 2 numbers first (common cases)
    for (int num : goodNumbers) {
        if (num == n) {
            return {num};
        }
    }
    for (int num : goodNumbers) {
        if (num < n && find(goodNumbers.begin(), goodNumbers.end(), n - num) != goodNumbers.end()) {
            return {num, n - num};
        }
    }
    // If not found, use 1's (since 1 is always good and sum of 1's can form any n)
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(1);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> goodNumbers = precomputeGoodNumbers();
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> solution = solve(n, goodNumbers);
        cout << solution.size() << "\n";
        for (int num : solution) {
            cout << num << " ";
        }
        cout << "\n";
    }
    
    return 0;
}