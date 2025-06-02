#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Variables to track current state
    int current_speed = 0;
    // Stack to keep track of active speed limits (top is the most recent)
    stack<int> speed_limits;
    // Overtake allowed state
    bool overtake_allowed = true;
    // Counter for minimal number of signs to ignore
    int res = 0;

    // For "no overtake allowed" signs that are currently active
    int no_overtake_cnt = 0;

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;

        if (t == 1) {
            // Polycarp changes speed
            int s;
            cin >> s;
            current_speed = s;

            // Check if current speed violates any active speed limit
            // Remove all speed limits that are less than current speed (need to ignore them)
            while (!speed_limits.empty() && current_speed > speed_limits.top()) {
                ++res;
                speed_limits.pop();
            }
        } else if (t == 2) {
            // Polycarp overtakes another car
            // If overtake is not allowed, need to ignore all active "no overtake allowed" signs
            if (!overtake_allowed) {
                res += no_overtake_cnt;
                no_overtake_cnt = 0;
                overtake_allowed = true;
            }
        } else if (t == 3) {
            // Polycarp goes past a "speed limit" sign
            int s;
            cin >> s;
            // Push new speed limit
            speed_limits.push(s);
            // If current speed already violates the new limit, need to ignore this sign
            if (current_speed > s) {
                ++res;
                speed_limits.pop();
            }
        } else if (t == 4) {
            // Polycarp goes past an "overtake is allowed" sign
            overtake_allowed = true;
            no_overtake_cnt = 0;
        } else if (t == 5) {
            // Polycarp goes past a "no speed limit" sign
            // Remove all speed limits
            while (!speed_limits.empty()) speed_limits.pop();
        } else if (t == 6) {
            // Polycarp goes past a "no overtake allowed" sign
            // If overtake is already not allowed, just increment the count
            if (!overtake_allowed) {
                ++no_overtake_cnt;
            } else {
                overtake_allowed = false;
                no_overtake_cnt = 1;
            }
        }
    }

    cout << res << '\n';
    return 0;
}