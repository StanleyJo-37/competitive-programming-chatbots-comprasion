#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    deque<int> dq;
    vector<pair<int, int>> initial_operations;

    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        dq.push_back(num);
    }

    // The first (n-1) operations will have unique A and B pairs.
    // After that, the pattern repeats with the maximum element at the front.
    for (int i = 0; i < n - 1; ++i) {
        int A = dq.front(); dq.pop_front();
        int B = dq.front(); dq.pop_front();
        initial_operations.emplace_back(A, B);
        if (A > B) {
            dq.push_front(A);
            dq.push_back(B);
        } else {
            dq.push_front(B);
            dq.push_back(A);
        }
    }

    // The maximum element is now at the front, and the rest cycle every (n-1) operations.
    int max_element = dq.front();
    dq.pop_front();
    vector<int> cycle_elements;
    while (!dq.empty()) {
        cycle_elements.push_back(dq.front());
        dq.pop_front();
    }

    // Process each query.
    while (q--) {
        long long m;
        cin >> m;
        if (m <= initial_operations.size()) {
            // The query is within the initial (n-1) operations.
            cout << initial_operations[m - 1].first << " " << initial_operations[m - 1].second << '\n';
        } else {
            // The query is in the repeating cycle.
            // The cycle starts after (n-1) operations and repeats every (n-1) operations.
            long long cycle_pos = (m - initial_operations.size() - 1) % (n - 1);
            cout << max_element << " " << cycle_elements[cycle_pos] << '\n';
        }
    }

    return 0;
}