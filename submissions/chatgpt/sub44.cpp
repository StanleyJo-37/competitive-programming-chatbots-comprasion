#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

// Struct to store runner's information
struct Runner {
    string name;
    double a; // time for 1st leg
    double b; // time for other legs
};

int main() {
    int n;
    cin >> n;
    vector<Runner> runners(n);
    for (int i = 0; i < n; ++i) {
        cin >> runners[i].name >> runners[i].a >> runners[i].b;
    }

    double best_time = 1e9; // initialize with a large value
    vector<string> best_team(4);

    // Try every runner as the 1st leg
    for (int i = 0; i < n; ++i) {
        // Collect all other runners for 2nd, 3rd, 4th legs
        vector<pair<double, int>> others;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue; // skip the 1st leg runner
            others.push_back({runners[j].b, j});
        }
        // Sort by b time (ascending)
        sort(others.begin(), others.end());
        // Only need the 3 fastest for the other legs
        double total = runners[i].a;
        vector<string> team(4);
        team[0] = runners[i].name;
        for (int k = 0; k < 3; ++k) {
            total += runners[others[k].second].b;
            team[k+1] = runners[others[k].second].name;
        }
        // Update best if this team is faster
        if (total < best_time) {
            best_time = total;
            best_team = team;
        }
    }

    // Output with required precision
    cout << fixed << setprecision(2) << best_time << endl;
    for (int i = 0; i < 4; ++i) {
        cout << best_team[i] << endl;
    }
    return 0;
}