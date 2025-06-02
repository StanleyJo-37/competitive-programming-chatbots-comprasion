#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); // Fast IO
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        // Sort the measurements to easily remove K smallest and K largest
        sort(A.begin(), A.end());

        // Calculate the sum of the remaining N-2K elements
        long long sum = 0;
        for (int i = K; i < N - K; ++i) {
            sum += A[i];
        }

        // Calculate the average as double
        double avg = (double)sum / (N - 2 * K);

        // Output the result with 6 decimal places
        cout << fixed << setprecision(6) << avg << '\n;
    }
    return 0;
}