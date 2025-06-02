#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int N = S.size();

        // Find positions of all soldiers ('1')
        vector<int> pos;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '1') pos.push_back(i);
        }
        int K = pos.size();

        // If there are no soldiers or all soldiers are already at the rightmost positions, answer is 0
        if (K == 0) {
            cout << 0 << '\n';
            continue;
        }
        bool already_rightmost = true;
        for (int i = 0; i < K; ++i) {
            if (pos[i] != N - K + i) {
                already_rightmost = false;
                break;
            }
        }
        if (already_rightmost) {
            cout << 0 << '\n';
            continue;
        }

        // To maximize the time, always move the leftmost movable soldier as far as possible
        // At each step, the leftmost soldier can move to the first available position from the right
        // We simulate the process greedily

        // Copy positions to simulate movement
        vector<int> soldiers = pos;
        int total_time = 0;

        // The rightmost K positions are: N-K, N-K+1, ..., N-1
        // We want to move soldiers to these positions in order

        // We process from the rightmost soldier to the leftmost
        // At each step, move the leftmost soldier that can move, as far as possible
        // The i-th rightmost position should be occupied by a soldier, so we move the leftmost soldier to that position

        // We process from the last soldier to the first
        for (int i = K - 1; i >= 0; --i) {
            // The target position for this soldier is N - K + i
            int target = N - K + i;
            // If the current soldier is already at the target, do nothing
            if (soldiers[i] == target) continue;
            // The soldier must move (target - soldiers[i]) steps
            // 1 second to choose, (target - soldiers[i]) seconds to move
            total_time += 1 + (target - soldiers[i]);
            // After moving, update the position
            soldiers[i] = target;
            // All soldiers to the left must not overtake this one, so their targets are to the left
        }

        cout << total_time << '\n';
    }
    return 0;
}