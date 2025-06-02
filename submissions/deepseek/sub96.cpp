#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int k, n, m;
        cin >> k >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];
        
        vector<int> res;
        int i = 0, j = 0;
        int currentLines = k;
        bool possible = true;
        
        while (i < n || j < m) {
            bool progress = false;
            
            // Try to process Monocarp's action if possible
            if (i < n) {
                if (a[i] == 0) {
                    res.push_back(0);
                    currentLines++;
                    i++;
                    progress = true;
                } else if (a[i] <= currentLines) {
                    res.push_back(a[i]);
                    i++;
                    progress = true;
                }
            }
            
            // If Monocarp's action wasn't processed, try Polycarp's
            if (!progress && j < m) {
                if (b[j] == 0) {
                    res.push_back(0);
                    currentLines++;
                    j++;
                    progress = true;
                } else if (b[j] <= currentLines) {
                    res.push_back(b[j]);
                    j++;
                    progress = true;
                }
            }
            
            // If no progress was made, the sequence is impossible
            if (!progress) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            for (int num : res) cout << num << " ";
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}