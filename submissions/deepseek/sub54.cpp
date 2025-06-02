#include <iostream>
#include <vector>

using namespace std;

// Function to compute the nth term of the Hofstadter Q sequence
int hofstadterQ(int n) {
    // Base cases: Q(1) = Q(2) = 1
    if (n == 1 || n == 2) {
        return 1;
    }
    
    // Dynamic programming approach to store computed values
    vector<int> q(n + 1);
    q[1] = q[2] = 1;
    
    // Compute Q(i) for i from 3 to n
    for (int i = 3; i <= n; ++i) {
        q[i] = q[i - q[i - 1]] + q[i - q[i - 2]];
    }
    
    return q[n];
}

int main() {
    int n;
    cin >> n; // Read input n
    
    // Output the nth term of the Hofstadter Q sequence
    cout << hofstadterQ(n) << endl;
    
    return 0;
}