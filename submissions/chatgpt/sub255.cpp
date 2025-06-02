#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int n;
    long long U;
    cin >> n >> U;
    vector<long long> E(n);
    for (int i = 0; i < n; ++i) {
        cin >> E[i];
    }

    // Initialize the maximum efficiency to -1 (impossible case)
    double max_eta = -1.0;

    // We use two pointers: i (start), k (end)
    // For each i, we want to find the largest k > i+1 such that E[k] - E[i] <= U
    int k = 2; // k must be at least i+2 (since we need i < j < k)
    for (int i = 0; i < n - 2; ++i) {
        // Move k as far as possible such that E[k] - E[i] <= U
        // k must be at least i+2
        while (k < n && E[k] - E[i] <= U) {
            ++k;
        }
        // After the loop, k is the first index where E[k] - E[i] > U, so k-1 is the last valid
        if (k - 1 > i + 1) {
            // j = i+1 (since E is strictly increasing, this gives the largest E[j])
            int j = i + 1;
            int kk = k - 1;
            // Calculate efficiency
            double eta = (double)(E[kk] - E[j]) / (E[kk] - E[i]);
            if (eta > max_eta) {
                max_eta = eta;
            }
        }
        // No need to move k back, since E is strictly increasing and k only moves forward
    }

    // Output the result with sufficient precision
    if (max_eta < 0) {
        cout << -1 << endl;
    } else {
        cout << fixed << setprecision(12) << max_eta << endl;
    }
    return 0;
}