#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read n and q
    int n, q;
    cin >> n >> q;

    // Read the initial deque
    deque<long long> dq(n);
    long long max_elem = 0;
    int max_pos = 0;
    for (int i = 0; i < n; ++i) {
        cin >> dq[i];
        // Find the maximum element and its position
        if (dq[i] > max_elem) {
            max_elem = dq[i];
            max_pos = i;
        }
    }

    // Store the first n-1 operations (before the max is at the front)
    vector<pair<long long, long long>> first_ops;
    deque<long long> temp_dq = dq;
    // Simulate until the max element is at the front
    while (temp_dq.front() != max_elem) {
        long long A = temp_dq.front(); temp_dq.pop_front();
        long long B = temp_dq.front(); temp_dq.pop_front();
        first_ops.emplace_back(A, B);
        // Place the larger at the front, smaller at the back
        if (A > B) {
            temp_dq.push_front(A);
            temp_dq.push_back(B);
        } else {
            temp_dq.push_front(B);
            temp_dq.push_back(A);
        }
    }

    // After the max is at the front, the sequence cycles
    // The cycle is: max_elem at front, then the rest in order
    // For each cycle operation, the pair is (max_elem, x), where x is the next element in the cycle
    vector<long long> cycle;
    temp_dq.pop_front(); // Remove max_elem
    while (!temp_dq.empty()) {
        cycle.push_back(temp_dq.front());
        temp_dq.pop_front();
    }
    int cycle_len = n - 1;

    // Process queries
    for (int i = 0; i < q; ++i) {
        long long m;
        cin >> m;
        if (m <= (long long)first_ops.size()) {
            // Before the cycle starts
            cout << first_ops[m-1].first << " " << first_ops[m-1].second << '\n';
        } else {
            // In the cycle
            long long idx = (m - (long long)first_ops.size() - 1) % cycle_len;
            cout << max_elem << " " << cycle[idx] << '\n';
        }
    }
    return 0;
}