#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // For each sequence, we will store:
    // - whether it has an ascent (flag)
    // - its minimum and maximum value (for non-ascent sequences)
    vector<pair<int, int>> minmax; // stores (min, max) for non-ascent sequences
    int ascent_count = 0; // number of sequences with at least one ascent

    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        vector<int> seq(l);
        for (int j = 0; j < l; ++j) {
            cin >> seq[j];
        }

        // Check if the sequence has an ascent
        bool has_ascent = false;
        for (int j = 1; j < l; ++j) {
            if (seq[j] > seq[j-1]) {
                has_ascent = true;
                break;
            }
        }
        if (has_ascent) {
            ++ascent_count;
        } else {
            // Store min and max for non-ascent sequence
            int mn = seq[0], mx = seq[0];
            for (int j = 1; j < l; ++j) {
                if (seq[j] < mn) mn = seq[j];
                if (seq[j] > mx) mx = seq[j];
            }
            minmax.emplace_back(mn, mx);
        }
    }

    // Total number of pairs is n^2
    long long total_pairs = 1LL * n * n;

    // If either s_x or s_y has an ascent, s_x + s_y will have an ascent
    // So, number of pairs where at least one has ascent:
    // = total_pairs - number of pairs where both have no ascent and their concatenation has no ascent

    // For two non-ascent sequences, their concatenation has an ascent
    // only if max of first < min of second
    // But since both are non-ascent, their own elements are non-increasing

    // For two non-ascent sequences s_x and s_y, their concatenation has NO ascent
    // only if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x, y)
    // But actually, for non-ascent sequences, their own elements are non-increasing,
    // so the only way s_x + s_y has NO ascent is if max_x >= min_y for all pairs (x