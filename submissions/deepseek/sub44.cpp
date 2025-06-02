#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Runner {
    string name;
    double firstLeg;
    double otherLegs;
};

int main() {
    int n;
    cin >> n;
    vector<Runner> runners(n);
    for (int i = 0; i < n; ++i) {
        cin >> runners[i].name >> runners[i].firstLeg >> runners[i].otherLegs;
    }

    double minTime = numeric_limits<double>::max();
    vector<string> bestTeam(4);

    // Iterate all possible combinations of 4 distinct runners
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                for (int l = 0; l < n; ++l) {
                    if (l == i || l == j || l == k) continue;

                    // Try all permutations of the 4 runners to assign legs
                    // The first leg must be assigned to one of the 4, others to the remaining 3
                    // We need to find the best assignment of legs to minimize total time
                    double currentTime = runners[i].firstLeg + runners[j].otherLegs + runners[k].otherLegs + runners[l].otherLegs;
                    if (currentTime < minTime) {
                        minTime = currentTime;
                        bestTeam[0] = runners[i].name;
                        bestTeam[1] = runners[j].name;
                        bestTeam[2] = runners[k].name;
                        bestTeam[3] = runners[l].name;
                    }

                    currentTime = runners[j].firstLeg + runners[i].otherLegs + runners[k].otherLegs + runners[l].otherLegs;
                    if (currentTime < minTime) {
                        minTime = currentTime;
                        bestTeam[0] = runners[j].name;
                        bestTeam[1] = runners[i].name;
                        bestTeam[2] = runners[k].name;
                        bestTeam[3] = runners[l].name;
                    }

                    currentTime = runners[k].firstLeg + runners[i].otherLegs + runners[j].otherLegs + runners[l].otherLegs;
                    if (currentTime < minTime) {
                        minTime = currentTime;
                        bestTeam[0] = runners[k].name;
                        bestTeam[1] = runners[i].name;
                        bestTeam[2] = runners[j].name;
                        bestTeam[3] = runners[l].name;
                    }

                    currentTime = runners[l].firstLeg + runners[i].otherLegs + runners[j].otherLegs + runners[k].otherLegs;
                    if (currentTime < minTime) {
                        minTime = currentTime;
                        bestTeam[0] = runners[l].name;
                        bestTeam[1] = runners[i].name;
                        bestTeam[2] = runners[j].name;
                        bestTeam[3] = runners[k].name;
                    }
                }
            }
        }
    }

    // Output the minimal time and the best team
    cout << fixed << setprecision(2) << minTime << endl;
    for (const string& name : bestTeam) {
        cout << name << endl;
    }

    return 0;
}