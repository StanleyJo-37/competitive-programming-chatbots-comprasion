#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    vector<int> perm(k);
    for (int i = 0; i < k; ++i) {
        perm[i] = i; // Initialize permutation as identity
    }

    int min_diff = INT_MAX;

    do {
        vector<int> transformed;
        for (const string& num : numbers) {
            string temp(k, '0');
            for (int i = 0; i < k; ++i) {
                temp[i] = num[perm[i]]; // Apply permutation to each digit
            }
            transformed.push_back(stoi(temp)); // Convert to integer
        }
        // Find max and min in the transformed numbers
        int current_max = *max_element(transformed.begin(), transformed.end());
        int current_min = *min_element(transformed.begin(), transformed.end());
        int diff = current_max - current_min;
        if (diff < min_diff) {
            min_diff = diff; // Update minimum difference found
        }
    } while (next_permutation(perm.begin(), perm.end())); // Try all permutations

    cout << min_diff << endl;
    return 0;
}