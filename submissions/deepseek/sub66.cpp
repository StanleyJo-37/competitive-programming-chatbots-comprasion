#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> items(k);
    for (int i = 0; i < k; ++i) {
        cin >> items[i];
    }
    
    int total_time = 0;
    
    for (int i = 0; i < n; ++i) {
        vector<int> order(m);
        for (int j = 0; j < m; ++j) {
            cin >> order[j];
        }
        
        for (int item : order) {
            // Find the position of the current item in the items vector
            auto it = find(items.begin(), items.end(), item);
            int pos = distance(items.begin(), it) + 1; // 1-based index
            total_time += pos;
            
            // Move the item to the front
            items.erase(it);
            items.insert(items.begin(), item);
        }
    }
    
    cout << total_time << endl;
    
    return 0;
}