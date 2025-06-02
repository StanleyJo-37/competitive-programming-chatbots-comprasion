#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        // Sort the array to efficiently count students with scores <= A[i] and > A[i]
        vector<int> sortedA = A;
        sort(sortedA.begin(), sortedA.end());
        
        int boastCount = 0;
        for (int i = 0; i < N; ++i) {
            int currentScore = A[i];
            // Find the first occurrence of a score greater than currentScore
            auto upper = upper_bound(sortedA.begin(), sortedA.end(), currentScore);
            int lessOrEqual = upper - sortedA.begin();
            int greater = sortedA.end() - upper;
            
            if (lessOrEqual > greater) {
                boastCount++;
            }
        }
        cout << boastCount << endl;
    }
    return 0;
}