#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K;
    string S;
    cin >> N >> K >> S;
    
    // We'll use a queue to keep track of the flips that affect the current position.
    queue<int> flipQueue;
    int flipCount = 0; // Tracks the number of flips affecting the current position.
    
    for (int i = 0; i < N; ++i) {
        // Remove flips that are no longer in the window.
        while (!flipQueue.empty() && flipQueue.front() <= i - K) {
            flipQueue.pop();
            flipCount--;
        }
        
        // Determine the effective value of S[i] after flips.
        bool current = (S[i] - '0') ^ (flipCount % 2);
        
        // If the current bit is 1, flip it by starting a new flip here (if possible).
        if (current == 1 && i <= N - K) {
            flipQueue.push(i);
            flipCount++;
            current ^= 1; // The flip affects the current bit immediately.
        }
        
        S[i] = current + '0';
    }
    
    cout << S << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}