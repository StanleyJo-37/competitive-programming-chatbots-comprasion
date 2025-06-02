#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, U;
    cin >> n >> U;
    vector<int> E(n);
    for (int i = 0; i < n; ++i) {
        cin >> E[i];
    }

    double max_eta = -1.0;
    // We need to find i < j < k such that E[k] - E[i] <= U
    // The goal is to maximize (E[k] - E[j]) / (E[k] - E[i])
    // To maximize this, for a fixed i and k, j should be as close to i as possible (i+1)
    // So for each i, find the largest possible k where E[k] - E[i] <= U, then j = i+1
    for (int i = 0, k = 0; i < n - 2; ++i) {
        // Find the largest k where E[k] - E[i] <= U
        while (k < n && E[k] - E[i] <= U) {
            k++;
        }
        k--; // The last valid k
        if (k >= i + 2) { // Ensure there's at least one j between i and k
            double current_eta = (double)(E[k] - E[i+1]) / (E[k] - E[i]);
            if (current_eta > max_eta) {
                max_eta = current_eta;
            }
        }
    }

    if (max_eta < 0) {
        cout << -1 << endl;
    } else {
        cout << fixed << setprecision(15) << max_eta << endl;
    }

    return 0;
}