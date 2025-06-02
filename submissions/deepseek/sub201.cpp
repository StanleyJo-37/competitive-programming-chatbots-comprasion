#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        sort(A.begin(), A.end()); // Sort to easily remove K smallest and largest elements
        double sum = 0;
        int count = N - 2 * K; // Remaining elements after removal
        for (int i = K; i < N - K; ++i) { // Iterate from K to N-K-1 (0-based)
            sum += A[i];
        }
        double average = sum / count;
        cout << fixed << setprecision(6) << average << endl; // Ensure 6 decimal places precision
    }
    return 0;
}