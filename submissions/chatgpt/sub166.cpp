#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int N, K;
        cin >> N >> K; // Read length of track and max distance at best speed
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i]; // Read number of girls in each kilometre
        }

        // Use sliding window to find the maximum sum of any K consecutive elements
        int current_sum = 0;
        // Calculate sum of first K elements
        for (int i = 0; i < K; ++i) {
            current_sum += a[i];
        }
        int max_sum = current_sum;

        // Slide the window from position 1 to N-K
        for (int i = K; i < N; ++i) {
            // Subtract the element going out of the window and add the new element
            current_sum = current_sum - a[i - K] + a[i];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }

        // Output the result for this test case
        cout << max_sum << endl;
    }
    return 0;
}