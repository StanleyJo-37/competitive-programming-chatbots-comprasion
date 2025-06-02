#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int A, B;
        unsigned int N;
        cin >> A >> B >> N;

        // If A == B, no operation is needed
        if (A == B) {
            cout << 0 << endl;
            continue;
        }

        int C = A ^ B; // The value we need to XOR to A to get B

        // If N == 1, we cannot choose any X (since 1 ≤ X < N), so impossible unless A == B
        if (N == 1) {
            cout << -1 << endl;
            continue;
        }

        // If C < N, we can do it in one operation (choose X = C)
        if (C < N) {
            cout << 1 << endl;
            continue;
        }

        // For N >= 2, we can always use at most 2 operations:
        // Since any integer C can be written as the XOR of two numbers less than N (if N > 1)
        // For C >= N, we can split C into two numbers X and Y such that 1 ≤ X, Y < N and X ^ Y = C
        // Let's try to find such X and Y

        // For N == 2, the only possible X is 1
        // So, if C >= 2, it's not possible
        if (N == 2) {
            // Only possible C is 1
            cout << -1 << endl;
            continue;
        }

        // For general N >= 3, we can always write C as the XOR of two numbers less than N
        // Let's try to find such a pair (X, Y)
        // For any C >= N, we can pick X = 1, Y = C ^ 1
        // Check if Y < N and Y != 0 and Y != 1
        int X = 1;
        int Y = C ^ X;
        if (Y < N && Y != 0 && Y != X) {
            cout << 2 << endl;
        } else {
            // Try X = 2
            X = 2;
            Y = C ^ X;
            if (Y < N && Y != 0 && Y != X) {
                cout << 2 << endl;
            } else {
                // In general, for N >= 3, there always exists such a pair for C < 2*N-2
                // But for C >= 2*N-2, it's not possible
                // Let's check for all X in [1, N-1]
                bool found = false;
                for (int X = 1; X < N; ++X) {
                    int Y = C ^ X;
                    if (Y < N && Y != 0 && Y != X) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    cout << 2 << endl;
                } else {
                    cout << -1 << endl;
                }
            }
        }
    }
    return 0;
}