#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N, X;
        cin >> N >> X;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        // The minimum time is the maximum between:
        // 1. The ceiling of X divided by the minimum shop capacity (since the bottleneck is the shop with the smallest capacity).
        // 2. The number of shops (since each admin must visit each shop once, requiring at least N hours).
        int min_capacity = *min_element(A.begin(), A.end());
        int time = max((X + min_capacity - 1) / min_capacity, N);
        cout << time << '\n';
    }
    
    return 0;
}