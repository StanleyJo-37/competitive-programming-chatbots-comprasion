#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main() {
    int format;
    string time;
    cin >> format >> time;

    // Extract original digits
    int orig_h1 = time[0] - '0';
    int orig_h2 = time[1] - '0';
    int orig_m1 = time[3] - '0';
    int orig_m2 = time[4] - '0';

    int min_changes = INT_MAX;
    string best_time = "";

    // Brute force all possible valid times in the given format
    for (int h = 0; h < (format == 12 ? 12 : 24); ++h) {
        for (int m = 0; m < 60; ++m) {
            // For 12-hour format, hours must be from 1 to 12
            if (format == 12 && (h == 0)) continue;

            // Compose candidate time string
            int cand_h1 = h / 10;
            int cand_h2 = h % 10;
            int cand_m1 = m / 10;
            int cand_m2 = m % 10;

            // Count digit changes needed
            int changes = 0;
            if (cand_h1 != orig_h1) ++changes;
            if (cand_h2 != orig_h2) ++changes;
            if (cand_m1 != orig_m1) ++changes;
            if (cand_m2 != orig_m2) ++changes;

            // If this candidate is better, update best_time
            if (changes < min_changes) {
                min_changes = changes;
                // Format as HH:MM
                best_time = "";
                best_time += (char)('0' + cand_h1);
                best_time += (char)('0' + cand_h2);
                best_time += ':';
                best_time += (char)('0' + cand_m1);
                best_time += (char)('0' + cand_m2);
            }
        }
    }

    cout << best_time << endl;
    return 0;
}