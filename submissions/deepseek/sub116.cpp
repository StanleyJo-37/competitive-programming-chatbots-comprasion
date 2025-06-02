#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int current_speed = 0;
    int speed_limit = 0;
    bool overtake_allowed = true;
    stack<int> speed_limits;
    int ignored_signs = 0;

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;

        if (t == 1) {
            // Event: Change speed
            cin >> current_speed;
            // Check if current speed exceeds the active speed limit
            while (!speed_limits.empty() && current_speed > speed_limits.top()) {
                ignored_signs++;
                speed_limits.pop();
            }
        } else if (t == 2) {
            // Event: Overtake
            if (!overtake_allowed) {
                // Overtake is not allowed, so we must ignore all 'no overtake' signs until an 'overtake allowed' is encountered
                ignored_signs++;
                // The actual signs ignored are handled by the stack logic, but here we just count the violation
            }
        } else if (t == 3) {
            // Event: Speed limit sign
            int new_limit;
            cin >> new_limit;
            if (current_speed > new_limit) {
                // Current speed exceeds the new limit, must ignore this sign
                ignored_signs++;
            } else {
                // Push the new limit onto the stack
                speed_limits.push(new_limit);
            }
        } else if (t == 4) {
            // Event: Overtake allowed
            overtake_allowed = true;
        } else if (t == 5) {
            // Event: No speed limit
            // Clear all speed limits
            while (!speed_limits.empty()) {
                speed_limits.pop();
            }
        } else if (t == 6) {
            // Event: No overtake allowed
            overtake_allowed = false;
        }
    }

    cout << ignored_signs << endl;
    return 0;
}