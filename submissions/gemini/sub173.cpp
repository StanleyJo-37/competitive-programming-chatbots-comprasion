#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solve() {
    string s;
    cin >> s;
    int n = s.length();

    vector<int> soldier_indices;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            soldier_indices.push_back(i);
        }
    }

    if (soldier_indices.empty()) {
        return 0;
    }

    long long total_time = 0;
    int rightmost_occupied_by_target = n - 1;

    for (int i = soldier_indices.size() - 1; i >= 0; --i) {
        int current_soldier_pos = soldier_indices[i];
        
        // Find the effective rightmost occupied cell by soldiers that are already in their final position or moved there
        while (rightmost_occupied_by_target >= 0 && s[rightmost_occupied_by_target] == '0') {
            rightmost_occupied_by_target--;
        }

        if (current_soldier_pos < rightmost_occupied_by_target) {
            // This soldier is not yet in its final rightmost position.
            // Move it to the leftmost available empty spot to the left of the current rightmost occupied cell.
            // This spot will be rightmost_occupied_by_target - 1.
            int target_pos = rightmost_occupied_by_target - 1;
            
            if (target_pos < current_soldier_pos) { // Soldier cannot move, it is blocked by another soldier already in place
                // This means the soldier is already at the correct relative position.
                // Or rather, it's blocked by the soldier to its right.
                // In the logic below, we find the leftmost available spot to the left of rightmost_occupied_by_target.
                // If it means current_soldier_pos can't move, it contributes 0.
                // This case is naturally handled if move_distance <= 0
            } else {
                long long move_distance = target_pos - current_soldier_pos;
                if (move_distance > 0) {
                    total_time += (move_distance + 1); // 1 second to choose + move_distance seconds to move
                    s[current_soldier_pos] = '0';
                    s[target_pos] = '1';
                    rightmost_occupied_by_target = target_pos; // Update the new rightmost occupied position
                }
            }
        }
    }

    return total_time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cout << solve() << endl;
    }

    return 0;
}