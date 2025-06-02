#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        // Sort the array to efficiently find the median and mean of any triplet
        sort(A.begin(), A.end());
        
        int min_beauty = INT_MAX;
        
        // Iterate through all possible middle elements (potential medians)
        for (int i = 1; i < N - 1; ++i) {
            int left = 0, right = N - 1;
            
            // Use two pointers to find the closest elements to A[i] to minimize |mean - median|
            while (left < i && right > i) {
                int sum = A[left] + A[i] + A[right];
                int mean = sum / 3;
                int beauty = 3 * abs(mean - A[i]);
                
                // Update the minimum beauty found
                if (beauty < min_beauty) {
                    min_beauty = beauty;
                    // Early exit if beauty is 0 (smallest possible)
                    if (min_beauty == 0) break;
                }
                
                // Move pointers to potentially find a smaller beauty
                if (sum < 3 * A[i]) {
                    left++;
                } else {
                    right--;
                }
            }
            
            if (min_beauty == 0) break;
        }
        
        cout << min_beauty << '\n';
    }
    
    return 0;
}