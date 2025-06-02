#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }

        int max_girls = 0;
        // Iterate through all possible starting positions of the K-length window
        for (int i = 0; i <= N - K; ++i) {
            int current_sum = 0;
            // Sum the girls in the current window of K kilometres
            for (int j = i; j < i + K; ++j) {
                current_sum += a[j];
            }
            // Update the maximum number of girls if current window is better
            if (current_sum > max_girls) {
                max_girls = current_sum;
            }
        }
        cout << max_girls << endl;
    }
    return 0;
}