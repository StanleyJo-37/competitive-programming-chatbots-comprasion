#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, l;
        cin >> n >> l;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Initialize positions and speeds of both cars
        double pos1 = 0, pos2 = l;
        double speed1 = 1, speed2 = 1;
        double time = 0;

        // Use two pointers to track the next flag for each car
        int left = 0, right = n - 1;

        while (pos1 < pos2) {
            // Calculate the time until the next event (either a flag or meeting)
            double timeToNextFlag1 = (left < n) ? (a[left] - pos1) / speed1 : 1e18;
            double timeToNextFlag2 = (right >= 0) ? (pos2 - a[right]) / speed2 : 1e18;
            double timeToMeet = (pos2 - pos1) / (speed1 + speed2);

            // Find the minimum time among the possible events
            double minTime = min(timeToMeet, min(timeToNextFlag1, timeToNextFlag2));

            // Update positions and time
            pos1 += minTime * speed1;
            pos2 -= minTime * speed2;
            time += minTime;

            // Check if the event was a flag for car1 or car2
            if (minTime == timeToNextFlag1 && left < n) {
                speed1 += 1;
                left++;
            }
            if (minTime == timeToNextFlag2 && right >= 0) {
                speed2 += 1;
                right--;
            }
        }

        // Output the result with high precision
        cout << fixed << setprecision(15) << time << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}