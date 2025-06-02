#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    unordered_map<int, int> freq;
    int left = 0, distinct = 0;
    int result_l = -1, result_r = -1;

    for (int right = 0; right < n; ++right) {
        // Increment frequency of current element
        if (freq[a[right]] == 0) {
            distinct++;
        }
        freq[a[right]]++;

        // If distinct elements exceed k, move left pointer
        while (distinct > k) {
            freq[a[left]]--;
            if (freq[a[left]] == 0) {
                distinct--;
            }
            left++;
        }

        // If distinct elements equals k, check for minimal by inclusion
        if (distinct == k) {
            // Try to minimize the segment by moving left as far as possible
            int temp_left = left;
            int temp_distinct = distinct;
            unordered_map<int, int> temp_freq = freq;
            while (temp_left <= right) {
                if (temp_freq[a[temp_left]] == 1) {
                    break;
                }
                temp_freq[a[temp_left]]--;
                temp_left++;
            }
            // Check if this segment is minimal by inclusion
            if (result_l == -1 || (right - temp_left < result_r - result_l)) {
                result_l = temp_left + 1; // converting to 1-based index
                result_r = right + 1;
            }
        }
    }

    if (result_l == -1) {
        cout << "-1 -1" << endl;
    } else {
        cout << result_l << " " << result_r << endl;
    }

    return 0;
}