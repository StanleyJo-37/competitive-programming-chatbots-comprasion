#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

bool is_c_valid(const vector<int>& c_indices) {
    if (c_indices.size() <= 2) {
        return true;
    }
    for (int i = 1; i < c_indices.size() - 1; ++i) {
        if (c_indices[i] - c_indices[i - 1] > c_indices[i + 1] - c_indices[i]) {
            return false;
        }
    }
    return true;
}

bool is_p_valid(const vector<int>& p_indices) {
    if (p_indices.size() <= 2) {
        return true;
    }
    for (int i = 1; i < p_indices.size() - 1; ++i) {
        if (p_indices[i] - p_indices[i - 1] < p_indices[i + 1] - p_indices[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long total_good_photos = 0;

        for (int i = 0; i < (1 << n); ++i) {
            vector<int> c_indices;
            vector<int> p_indices;
            long long sum_c = 0;
            long long sum_p = 0;

            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) { // Person j+1 holds 'C'
                    c_indices.push_back(j + 1);
                    sum_c += a[j];
                } else { // Person j+1 holds 'P'
                    p_indices.push_back(j + 1);
                    sum_p += a[j];
                }
            }

            if (is_c_valid(c_indices) && is_p_valid(p_indices) && sum_c < sum_p) {
                total_good_photos = (total_good_photos + 1) % MOD;
            }
        }
        cout << total_good_photos << "\n";
    }

    return 0;
}