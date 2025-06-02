#include <iostream>
#include <string>
#include <climits>

using namespace std;

int main() {
    int format;
    string time;
    cin >> format >> time;

    int minChanges = INT_MAX;
    string bestTime;

    // Iterate all possible valid times in the given format
    for (int h = 0; h < (format == 12 ? 12 : 24); ++h) {
        for (int m = 0; m < 60; ++m) {
            // Format the current time as HH:MM
            string candidate;
            if (h < 10) candidate += "0";
            candidate += to_string(h) + ":";
            if (m < 10) candidate += "0";
            candidate += to_string(m);

            // Calculate the number of changes needed
            int changes = 0;
            for (int i = 0; i < 5; ++i) {
                if (time[i] != candidate[i]) {
                    changes++;
                }
            }

            // Update the best time if fewer changes are needed
            if (changes < minChanges) {
                minChanges = changes;
                bestTime = candidate;
            }
        }
    }

    // Handle 12-hour format separately for hours 13-23 (since 12-hour format is 1-12)
    if (format == 12) {
        for (int h = 1; h <= 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                // Format the current time as HH:MM
                string candidate;
                if (h < 10) candidate += "0";
                candidate += to_string(h) + ":";
                if (m < 10) candidate += "0";
                candidate += to_string(m);

                // Calculate the number of changes needed
                int changes = 0;
                for (int i = 0; i < 5; ++i) {
                    if (time[i] != candidate[i]) {
                        changes++;
                    }
                }

                // Update the best time if fewer changes are needed
                if (changes < minChanges) {
                    minChanges = changes;
                    bestTime = candidate;
                }
            }
        }
    }

    cout << bestTime << endl;
    return 0;
}