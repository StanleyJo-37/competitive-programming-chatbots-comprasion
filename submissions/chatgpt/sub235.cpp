#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Store positions where "heavy" starts
    vector<int> heavy_pos;
    // Store positions where "metal" starts
    vector<int> metal_pos;

    // Find all starting indices of "heavy" and "metal"
    for (int i = 0; i <= n - 5; ++i) {
        if (s.substr(i, 5) == "heavy") {
            heavy_pos.push_back(i);
        }
        if (s.substr(i, 5) == "metal") {
            metal_pos.push_back(i);
        }
    }

    // Use two pointers to count all pairs (h, m) such that h < m
    long long ans = 0;
    int m = 0;
    int metal_cnt = metal_pos.size();
    for (int h = 0; h < (int)heavy_pos.size(); ++h) {
        // Move m pointer to the first "metal" that starts after "heavy"
        while (m < metal_cnt && metal_pos[m] <= heavy_pos[h]) {
            ++m;
        }
        // All "metal" starting from m are valid for this "heavy"
        ans += (metal_cnt - m);
    }

    cout << ans << endl;
    return 0;
}