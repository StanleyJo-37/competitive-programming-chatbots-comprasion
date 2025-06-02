#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    // For each test case
    while (t--) {
        int n;
        long long l;
        cin >> n >> l;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Two pointers: i for left car, j for right car
        int i = 0, j = n - 1;
        // Positions of left and right car
        double posL = 0.0, posR = (double)l;
        // Speeds of left and right car
        double speedL = 1.0, speedR = 1.0;
        // Time elapsed
        double time = 0.0;

        // While left pointer does not cross right pointer
        while (i <= j) {
            // Next flag for left car
            double nextFlagL = (i < n) ? a[i] : l;
            // Next flag for right car
            double nextFlagR = (j >= 0) ? a[j] : 0;

            // Time to reach next flag for left car
            double tL = (nextFlagL - posL) / speedL;
            // Time to reach next flag for right car
            double tR = (posR - nextFlagR) / speedR;

            // The car that reaches its next flag first
            if (tL < tR) {
                // Move both cars for tL seconds
                posL = nextFlagL;
                posR -= speedR * tL;
                time += tL;
                speedL += 1.0;
                i++;
            } else {
                // Move both cars for tR seconds
                posL += speedL * tR;
                posR = nextFlagR;
                time += tR;
                speedR += 1.0;
                j--;
            }
        }

        // After all flags are passed, cars move towards each other
        // Time to meet: (posR - posL) / (speedL + speedR)
        if (posL < posR) {
            double tMeet = (posR - posL) / (speedL + speedR);
            time += tMeet;
        }

        // Output with sufficient precision
        cout << fixed << setprecision(15) << time << '\n';
    }
    return 0;
}