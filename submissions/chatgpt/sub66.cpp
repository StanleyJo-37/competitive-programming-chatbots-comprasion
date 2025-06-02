#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k; // n: number of customers, m: items per customer, k: total items

    vector<int> row(k); // row: current arrangement of items
    for (int i = 0; i < k; ++i) {
        cin >> row[i]; // initial arrangement
    }

    int total_time = 0;

    // For each customer
    for (int i = 0; i < n; ++i) {
        vector<int> order(m);
        for (int j = 0; j < m; ++j) {
            cin >> order[j]; // items in the order
        }

        // For each item in the order
        for (int j = 0; j < m; ++j) {
            int item = order[j];
            // Find the position (1-based) of the item in the current row
            int pos = 0;
            for (; pos < k; ++pos) {
                if (row[pos] == item) break;
            }
            total_time += (pos + 1); // add position (1-based) to total time

            // Move the accessed item to the front of the row
            // Remove item at pos and insert at front
            row.erase(row.begin() + pos);
            row.insert(row.begin(), item);
        }
    }

    cout << total_time << endl;
    return 0;
}