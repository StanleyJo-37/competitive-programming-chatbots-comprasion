#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> s(n);
        int max1 = -1, max2 = -1; // max1: largest, max2: second largest

        // Read strengths and find max1 and max2
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
            if (s[i] > max1) {
                max2 = max1;
                max1 = s[i];
            } else if (s[i] > max2) {
                max2 = s[i];
            }
        }

        // For each participant, output s[i] - (max strength of others)
        for (int i = 0; i < n; ++i) {
            // If s[i] is the largest, the max among others is max2
            // Otherwise, the max among others is max1
            int diff = s[i] == max1 ? s[i] - max2 : s[i] - max1;
            cout << diff << (i == n-1 ? '\n' : ' ');
        }
    }
    return 0;
}