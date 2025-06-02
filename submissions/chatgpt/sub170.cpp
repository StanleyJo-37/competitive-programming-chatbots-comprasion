#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int N;
        cin >> N; // Read number of students
        vector<int> A(N);
        vector<int> freq(101, 0); // Frequency array for scores 0..100

        // Read scores and build frequency array
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            freq[A[i]]++;
        }

        // Build prefix sum of frequencies for quick range queries
        vector<int> prefix(101, 0);
        prefix[0] = freq[0];
        for (int i = 1; i <= 100; ++i) {
            prefix[i] = prefix[i-1] + freq[i];
        }

        int boast_count = 0;
        // For each student, check if they will boast
        for (int i = 0; i < N; ++i) {
            int score = A[i];
            // Number of students scoring less than or equal to A[i]
            int less_equal = prefix[score];
            // Number of students scoring greater than A[i]
            int greater = N - less_equal;
            // If less_equal > greater, student will boast
            if (less_equal > greater) {
                boast_count++;
            }
        }
        cout << boast_count << '\n';
    }
    return 0;
}