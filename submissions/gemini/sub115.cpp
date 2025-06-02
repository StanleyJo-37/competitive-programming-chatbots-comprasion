#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Adjacency list to store dependencies. adj[i] will store parts that depend on part i.
vector<vector<int>> adj;
// In-degree for each part. in_degree[i] will store the number of prerequisites for part i.
vector<int> in_degree;
// Computer location for each part. computer_loc[i] stores the computer where part i must be completed.
vector<int> computer_loc;
// Visited array to keep track of completed tasks.
vector<bool> visited;
// Number of game parts.
int n;

// Function to calculate the cost of moving between computers.
int get_move_cost(int from, int to) {
    if (from == to) return 0;
    if (from == 1 && to == 2) return 1;
    if (from == 1 && to == 3) return 2;
    if (from == 2 && to == 1) return 2;
    if (from == 2 && to == 3) return 1;
    if (from == 3 && to == 1) return 1;
    if (from == 3 && to == 2) return 2;
    return -1; // Should not happen
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    computer_loc.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> computer_loc[i];
    }

    adj.resize(n + 1);
    in_degree.resize(n + 1, 0);

    // Read dependencies and build the graph.
    // We reverse the dependencies to make it easier to decrement in-degrees
    // when a task is completed. adj[i] stores tasks that depend on task 'i'.
    // The problem statement gives us 'tasks that *must be completed before* task i'.
    // So if 'a' must be completed before 'i', then 'i' depends on 'a'.
    // We want to find tasks that have *no uncompleted dependencies*.
    // So, if 'a' is a prerequisite for 'i', then 'i' depends on 'a'.
    // When 'a' is completed, we need to decrement in_degree of 'i'.
    // So we add 'i' to adj[a].
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int prereq_part;
            cin >> prereq_part;
            adj[prereq_part].push_back(i); // If prereq_part is a prerequisite for i, then i depends on prereq_part.
            in_degree[i]++; // Increment in-degree of i, as it has one more prerequisite.
        }
    }

    // Initialize minimum time to a very large value.
    long long min_total_time = 1e18;

    // Iterate through all possible starting computers (1, 2, or 3).
    for (int start_computer = 1; start_computer <= 3; ++start_computer) {
        long long current_time = 0;
        int current_computer = start_computer;
        visited.assign(n + 1, false); // Reset visited tasks for each starting computer.

        // Create a copy of in_degree for the current simulation to avoid modifying the original.
        vector<int> temp_in_degree = in_degree;

        // Count of completed tasks.
        int completed_tasks_count = 0;

        // Loop until all tasks are completed.
        while (completed_tasks_count < n) {
            // Find all tasks that can be completed on the current computer and have no uncompleted dependencies.
            // A set is used here to maintain sorted order and easy removal, although for small N a vector and sort would also work.
            set<int> solvable_tasks_on_current_computer;
            for (int i = 1; i <= n; ++i) {
                if (!visited[i] && temp_in_degree[i] == 0 && computer_loc[i] == current_computer) {
                    solvable_tasks_on_current_computer.insert(i);
                }
            }

            // If there are tasks to complete on the current computer:
            if (!solvable_tasks_on_current_computer.empty()) {
                // Complete all such tasks.
                for (int task_id : solvable_tasks_on_current_computer) {
                    current_time++; // Each task takes 1 hour.
                    visited[task_id] = true; // Mark as visited.
                    completed_tasks_count++; // Increment count of completed tasks.

                    // For all tasks that depend on the just completed task_id, decrement their in-degree.
                    for (int dependent_task : adj[task_id]) {
                        temp_in_degree[dependent_task]--;
                    }
                }
            } else {
                // If no tasks can be completed on the current computer, we need to move.
                // Find the next best computer to move to.
                // We prioritize moving to a computer that has at least one task that can be started.
                int next_best_computer = -1;
                for (int target_computer = 1; target_computer <= 3; ++target_computer) {
                    if (target_computer == current_computer) continue; // Don't consider staying on the same computer.

                    bool can_find_task_on_target = false;
                    for (int i = 1; i <= n; ++i) {
                        if (!visited[i] && temp_in_degree[i] == 0 && computer_loc[i] == target_computer) {
                            can_find_task_on_target = true;
                            break;
                        }
                    }

                    if (can_find_task_on_target) {
                        // If we can find a task on the target computer, this is a potential candidate.
                        // We choose the one with the minimum move cost.
                        if (next_best_computer == -1 || get_move_cost(current_computer, target_computer) < get_move_cost(current_computer, next_best_computer)) {
                            next_best_computer = target_computer;
                        }
                    }
                }

                // If we found a next best computer to move to:
                if (next_best_computer != -1) {
                    current_time += get_move_cost(current_computer, next_best_computer); // Add movement cost.
                    current_computer = next_best_computer; // Update current computer.
                } else {
                    // This scenario means there are no available tasks on any computer.
                    // This implies that all remaining tasks have uncompleted dependencies,
                    // which means something is wrong or a cyclic dependency exists, but the problem guarantees no cyclic dependencies.
                    // Or, it means all remaining tasks are on computers where we cannot reach them without first completing tasks
                    // that are on the current computer (which we have already processed).
                    // This should theoretically not be reached if the graph is a DAG and solvable.
                    // However, it could be that we moved to a computer, completed all tasks there, and now there are no
                    // tasks on other computers with 0 in-degree. In such a case, we need to move again.
                    // The 'while (completed_tasks_count < n)' loop handles this implicitly by forcing another iteration.
                    // If we reach this 'else' block, it means we cannot progress.
                    // This logic implies that if we are stuck and cannot find a task on the current computer,
                    // nor can we find a path to a computer with an immediately solvable task, then the simulation will loop indefinitely.
                    // However, given the problem constraints (DAG), this shouldn't happen unless all remaining tasks
                    // require prerequisites that are currently on inaccessible computers.
                    // The correct logic is that we must always be able to find a task eventually, potentially after moving.
                    // If we reach here, it implies we are stuck without being able to complete all tasks.
                    // This should only happen if `completed_tasks_count < n` but we cannot find any task with `temp_in_degree[i] == 0`.
                    // This would violate the DAG property with guaranteed completion.
                    // The loop should always find a task to complete or a path to one, provided `completed_tasks_count < n`.

                    // If we get here, it means we ran out of options without completing all tasks.
                    // This implies a logical flaw in the greedy approach if it's supposed to find an optimal solution for all cases.
                    // However, the greedy approach here is to always complete available tasks on the current computer,
                    // then move to the nearest computer with an available task if none are available on the current.
                    // This is generally a good strategy for DAGs.
                    break; // Break to avoid infinite loop in case of logical error / unhandled edge case.
                }
            }
        }
        // Update the minimum total time.
        min_total_time = min(min_total_time, current_time);
    }

    cout << min_total_time << endl;

    return 0;
}