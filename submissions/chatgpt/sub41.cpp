#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// This function checks if it's possible to survive t hours with 'trains' trains in total.
// Each train has capacity k. We try to schedule the trains optimally.
bool canSurvive(int n, int t, long long k, const vector<long long>& a, const vector<long long>& b, const vector<long long>& c, int trains) {
    // people[i]: number of people at station i at the current hour
    vector<long long> people = a;
    // trainsLeft: how many trains we have left to use
    int trainsLeft = trains;
    // For each hour
    for (int hour = 0; hour < t; ++hour) {
        // For each station, check if after arrivals at the end of this hour, the number of people will exceed c_i
        bool needTrain = false;
        for (int i = 0; i < n; ++i) {
            if (people[i] + b[i] > c[i]) {
                needTrain = true;
                break;
            }
        }
        // If we need a train this hour, use as many as needed to avoid overflow after arrivals
        if (needTrain) {
            // Binary search: minimal number of trains needed this hour
            int low = 1, high = trainsLeft, best = -1;
            while (low <= high) {
                int mid = (low + high) / 2;
                // Simulate using 'mid' trains this hour
                vector<long long> temp = people;
                long long cap = mid * k;
                for (int i = 0; i < n; ++i) {
                    long long take = min(temp[i], cap);
                    temp[i] -= take;
                    cap -= take;
                    if (cap == 0) break;
                }
                // After train, arrivals
                bool ok = true;
                for (int i = 0; i < n; ++i) {
                    if (temp[i] + b[i] > c[i]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    best = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            if (best == -1 || best > trainsLeft) return false;
            // Use 'best' trains this hour
            trainsLeft -= best;
            // Remove people by train
            long long cap = best * k;
            for (int i = 0; i < n; ++i) {
                long long take = min(people[i], cap);
                people[i] -= take;
                cap -= take;
                if (cap == 0) break;
            }
        }
        // Arrivals at end of hour
        for (int i = 0; i < n; ++i) {
            people[i] += b[i];
            if (people[i] > c[i]) return false;
        }
    }
    return true;
}

int main() {
    int n, t;
    long long k;
    cin >> n >> t >> k;
    vector<long long> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    // Binary search for the minimal number of trains needed
    int left = 0, right = n * t, answer = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (canSurvive(n, t, k, a, b, c, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << answer << endl;
    return 0;
}