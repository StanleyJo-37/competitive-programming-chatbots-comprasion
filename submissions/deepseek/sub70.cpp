#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    // Precompute prefix maxima and record counts
    vector<int> prefix_max(n);
    vector<int> is_record(n, 0);
    int current_max = 0;
    int total_records = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] > current_max) {
            is_record[i] = 1;
            total_records++;
            current_max = p[i];
        }
        prefix_max[i] = current_max;
    }

    // For each element, compute how many records would be lost if it's removed,
    // and how many new records would be gained.
    vector<int> loss(n + 2, 0); // 1-based to n
    vector<int> gain(n + 2, 0); // 1-based to n

    // Compute loss: if p[i] is a record, removing it will lose 1 record
    for (int i = 0; i < n; ++i) {
        if (is_record[i]) {
            loss[i + 1] = 1;
        }
    }

    // Compute gain: if p[i] is not a record, check if removing the previous record
    // would allow p[i] to become a record.
    // Specifically, for each i, if p[i] > prefix_max[j-1] where j is the position
    // of the previous record before i, then removing that previous record would make p[i] a new record.
    // To optimize, we can track for each i, the previous record's position.
    vector<int> prev_record_pos(n, -1);
    int last_record_pos = -1;
    for (int i = 0; i < n; ++i) {
        prev_record_pos[i] = last_record_pos;
        if (is_record[i]) {
            last_record_pos = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!is_record[i]) {
            int prev_pos = prev_record_pos[i];
            int prev_max = (prev_pos == -1) ? 0 : prefix_max[prev_pos];
            if (p[i] > prev_max) {
                // The previous record is the one blocking p[i] from being a record.
                // So, removing the previous record would make p[i] a new record.
                gain[prev_pos + 1]++;
            }
        }
    }

    // Now, for each element, compute the net effect (total_records - loss[i] + gain[i])
    // and find the element with the maximum net effect. If tie, choose the smallest element.
    int best_element = 1;
    int max_net = total_records - loss[1] + gain[1];
    for (int i = 2; i <= n; ++i) {
        int net = total_records - loss[i] + gain[i];
        if (net > max_net || (net == max_net && p[i - 1] < best_element)) {
            max_net = net;
            best_element = p[i - 1];
        }
    }

    cout << best_element << endl;

    return 0;
}