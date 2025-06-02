#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> min_vals(n), max_vals(n);
    vector<bool> has_ascent(n, false);

    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        vector<int> seq(l);
        for (int j = 0; j < l; ++j) {
            cin >> seq[j];
        }

        int min_val = seq[0], max_val = seq[0];
        bool ascent = false;
        for (int j = 1; j < l; ++j) {
            if (seq[j] > min_val) {
                ascent = true;
                break;
            }
            min_val = min(min_val, seq[j]);
            max_val = max(max_val, seq[j]);
        }
        has_ascent[i] = ascent;
        min_vals[i] = min_val;
        max_vals[i] = max_val;
    }

    // Count sequences that have an ascent (they can pair with any sequence)
    int ascent_count = count(has_ascent.begin(), has_ascent.end(), true);
    long long total_pairs = (long long)ascent_count * n * 2LL - (long long)ascent_count * ascent_count;

    // Now handle sequences without ascent: need s_x.min < s_y.max
    vector<int> max_without_ascent, min_without_ascent;
    for (int i = 0; i < n; ++i) {
        if (!has_ascent[i]) {
            max_without_ascent.push_back(max_vals[i]);
            min_without_ascent.push_back(min_vals[i]);
        }
    }

    sort(max_without_ascent.begin(), max_without_ascent.end());
    sort(min_without_ascent.begin(), min_without_ascent.end());

    long long valid_pairs = 0;
    for (int val : min_without_ascent) {
        // Number of max_vals > val in max_without_ascent
        auto it = upper_bound(max_without_ascent.begin(), max_without_ascent.end(), val);
        valid_pairs += max_without_ascent.end() - it;
    }

    total_pairs += valid_pairs;
    cout << total_pairs << '\n';

    return 0;
}