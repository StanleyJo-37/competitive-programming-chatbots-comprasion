#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // Not strictly needed for this final logic, but good practice.

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    int current_speed = 0; // Polycarp's current speed.

    // speed_limits_active_stack stores active speed limits from 'speed limit S' signs (type 3).
    // It is maintained as a monotonic stack (increasing from bottom to top),
    // so speed_limits_active_stack.top() always represents the most restrictive (smallest) active limit.
    // 'no speed limit' signs (type 5) clear all active speed limits.
    // This interpretation of speed limits (cumulative '3 S' signs, '5' clears all)
    // combined with immediate ignoring of '3 S' if current speed is too high,
    // matches the first example's output.
    std::stack<int> speed_limits_active_stack;

    // overtake_allowed_stack stores the state of overtaking.
    // 'overtake is allowed' (type 4) pushes true.
    // 'no overtake allowed' (type 6) pushes false.
    // Initially, overtake is allowed.
    // This interpretation of overtake signs (cumulative '4' and '6' signs)
    // matches the third example's output.
    std::stack<bool> overtake_allowed_stack;
    overtake_allowed_stack.push(true); // Initial state: overtake is allowed.

    int ignored_signs_count = 0;

    for (int i = 0; i < n; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) { // Polycarp changes speed to S
            int s;
            std::cin >> s;
            current_speed = s;
            // If Polycarp's current speed exceeds the most restrictive active limit
            // (which is speed_limits_active_stack.top() due to monotonic property),
            // he must ignore that limit sign. This is done greedily by popping
            // from the stack until the current speed is no longer a violation.
            while (!speed_limits_active_stack.empty() && speed_limits_active_stack.top() < current_speed) {
                speed_limits_active_stack.pop(); // Ignore this speed limit sign.
                ignored_signs_count++;
            }
        } else if (type == 2) { // Polycarp's car overtakes
            // If overtaking is currently not allowed (overtake_allowed_stack.top() is false),
            // Polycarp must ignore the 'no overtake allowed' signs that caused this state.
            // This is done greedily by popping from the stack until overtaking is allowed.
            while (!overtake_allowed_stack.empty() && !overtake_allowed_stack.top()) {
                overtake_allowed_stack.pop(); // Ignore this 'no overtake allowed' sign.
                ignored_signs_count++;
            }
        } else if (type == 3) { // Polycarp's car goes past "speed limit S" sign
            int s;
            std::cin >> s;
            // If Polycarp's current speed is already greater than the new limit S,
            // this sign must be ignored immediately to prevent an immediate violation.
            if (current_speed > s) {
                ignored_signs_count++;
            } else {
                // Otherwise, this speed limit becomes active.
                // To maintain the monotonic property of speed_limits_active_stack
                // (elements are increasing from bottom to top, so top is the minimum),
                // pop any limits from the stack that are greater than or equal to S.
                // This is because S will become the new most restrictive limit if it's smaller
                // than current top, or it's a new active limit that doesn't change the minimum.
                while (!speed_limits_active_stack.empty() && speed_limits_active_stack.top() > s) {
                    speed_limits_active_stack.pop();
                }
                speed_limits_active_stack.push(s);
            }
        } else if (type == 4) { // Polycarp's car goes past "overtake is allowed" sign
            // This sign allows overtaking. Push 'true' onto the stack.
            overtake_allowed_stack.push(true);
        } else if (type == 5) { // Polycarp's car goes past "no speed limit"
            // This sign cancels all previous speed limits.
            // So, clear the stack of active speed limits.
            speed_limits_active_stack = std::stack<int>(); // Reassigning with a new empty stack clears it.
        } else if (type == 6) { // Polycarp's car goes past "no overtake allowed"
            // This sign disallows overtaking. Push 'false' onto the stack.
            overtake_allowed_stack.push(false);
        }
    }

    std::cout << ignored_signs_count << std::endl;

    return 0;
}
