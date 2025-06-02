#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    // Edge case: if n == 1, only element can be removed
    if (n == 1) {
        cout << p[0] << '\n';
        return 0;
    }

    // Precompute prefix maximums
    vector<int> prefix_max(n);
    prefix_max[0] = p[0];
    for (int i = 1; i < n; ++i)
        prefix_max[i] = max(prefix_max[i-1], p[i]);

    // Precompute suffix maximums
    vector<int> suffix_max(n);
    suffix_max[n-1] = p[n-1];
    for (int i = n-2; i >= 0; --i)
        suffix_max[i] = max(suffix_max[i+1], p[i]);

    // Precompute prefix record counts
    vector<int> prefix_rec(n);
    int rec = 0, cur_max = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] > cur_max) {
            ++rec;
            cur_max = p[i];
        }
        prefix_rec[i] = rec;
    }

    // Precompute suffix record counts
    vector<int> suffix_rec(n);
    rec = 0, cur_max = 0;
    for (int i = n-1; i >= 0; --i) {
        if (p[i] > cur_max) {
            ++rec;
            cur_max = p[i];
        }
        suffix_rec[i] = rec;
    }

    // For each position, calculate number of records after removing p[i]
    // and keep track of the maximum and the smallest element to remove
    int max_records = 0;
    int answer = 1e9+7; // p[i] <= n <= 1e5, so this is safe

    for (int i = 0; i < n; ++i) {
        // Number of records in prefix (before i)
        int left_rec = (i == 0) ? 0 : prefix_rec[i-1];
        // Number of records in suffix (after i)
        int right_rec = (i == n-1) ? 0 : suffix_rec[i+1];

        // The maximum value before i
        int left_max = (i == 0) ? 0 : prefix_max[i-1];
        // The maximum value after i
        int right_max = (i == n-1) ? 0 : suffix_max[i+1];

        // If left_max < right_max, then right_max will be a new record after left_max
        // So, we need to check if right_max is already counted as a record in the suffix
        // But since we are removing p[i], the suffix starts at i+1, so right_max is the first element in the suffix
        // If left_max < right_max, then right_max will be a record after removing p[i]
        // But if left_max >= right_max, then all records in the suffix are not new records

        int total_records = left_rec;
        if (i != n-1) {
            // Find the first record in the suffix (after i)
            // The first record in the suffix is always p[i+1] if p[i+1] > left_max
            // We need to count how many records in the suffix are greater than left_max
            int cnt = 0;
            int cur = left_max;
            for (int j = i+1; j < n; ++j) {
                if (p[j] > cur) {
                    ++cnt;
                    cur = p[j];
                }
            }
            total_records += cnt;
        }
        // If i == n-1, no suffix, so total_records = left_rec

        // Update answer if we get more records, or same but smaller p[i]
        if (total_records > max_records) {
            max_records = total_records;
            answer = p[i];
        } else if (total_records == max_records) {
            answer = min(answer, p[i]);
        }
    }

    cout << answer << '\n';
    return 0;
}